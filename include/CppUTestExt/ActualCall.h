/*
 * Copyright (c) 2018, Stephen Holstein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ACTUAL_CALL_H
#define ACTUAL_CALL_H

#include "CppUTestExt/TestDouble.h"
#include "CppUTest/TestHarness.h"

#include <typeinfo>

class ActualCall;
/// implemented in TestDouble.cpp
ActualCall actualCall( const SimpleString& name );

class ActualCall
{
public:
  const SimpleString      name;

  ActualCall( const SimpleString& _name ) : name(_name) { }

  /// match this against expectations if not already returned
  ~ActualCall();

  template<typename T>
  ActualCall& with( const SimpleString& _name, const T& value )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, value );
    _parameters = new TestDouble::ParameterChain( pParameter, _parameters );
    return *this;
  }

  ActualCall& withBuffer( const SimpleString& _name, const void* staticBuffer, const std::size_t& size )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, staticBuffer, size );
    _parameters = new TestDouble::ParameterChain( pParameter, _parameters );
    return *this;
  }
  // template<typename T>
  // ActualCall& with( const SimpleString& _name, T* const buffer, const std::size_t& size )
  // {
  //   TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, buffer, size );
  //   _parameters = new TestDouble::ParameterChain( pParameter, _parameters );
  //   return *this;
  // }

  template<typename T>
  ActualCall& output( const SimpleString& _name, T* const pValue, const T defaultValue=T(true) )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, pValue, defaultValue, true );
    _outputs = new TestDouble::ParameterChain( pParameter, _outputs );
    return *this;
  }

  ActualCall& output( const SimpleString& _name, void* const buffer, const std::size_t& size, const void* const defaultBuffer=0 )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, buffer, size, defaultBuffer );
    _outputs = new TestDouble::ParameterChain( pParameter, _outputs );
    return *this;
  }

  /// sets outputs
  void returns();

  //  return based methods invoke matched expectation (or else do nothing and return 0)
  bool returnBool();
  char returnChar();
  unsigned char returnUnsignedChar();
  int returnInt();
  unsigned int returnUnsignedInt();
  long int returnLongInt();
  unsigned long int returnUnsignedLongInt();
  long long int returnLongLongInt();
  unsigned long long int returnUnsignedLongLongInt();
  float returnFloat();
  double returnDouble();
  void* returnPointer();
  const void* returnConstPointer();
  void(*returnFunctionPointer())();

  const TestDouble::ParameterChain* getParameters() const { return _parameters; }
  TestDouble::ParameterChain* getOutputs() const { return _outputs; }

private:
  TestDouble::ParameterChain*   _parameters = 0;
  TestDouble::ParameterChain*   _outputs = 0;
  bool  _returned = false;

  void _failActual();

};  // class ActualCall

#endif /* ACTUAL_CALL_H */
