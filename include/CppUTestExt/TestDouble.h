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
#ifndef TEST_DOUBLE_H
#define TEST_DOUBLE_H

#include "CppUTestExt/MockSupport.h"

#include <typeinfo>
#include <CppUTest/PlatformSpecificFunctions.h>

const static SimpleString TEST_DOUBLE_GLOBAL_CONTEXT = " ";

void checkExpectations( const SimpleString& context = TEST_DOUBLE_GLOBAL_CONTEXT );

class Expectation;
void addExpectation( const Expectation& expectation );

class Actual;
void checkActual( Actual& actual );

class Parameter
{
public:
  const SimpleString& name;
  const SimpleString  type;

  template<typename T>
  Parameter( const SimpleString& _name, const T& _value )
  : name(_name), type( typeid(_value).name() ), _variant(_value)
  { }

private:
  const union Variant {
    bool                    asBool;
    char                    asChar;
    unsigned char           asUnsignedChar;
    int                     asInt;
    unsigned int            asUnsignedInt;
    long int                asLongInt;
    unsigned long int       asUnsignedLongInt;
    long long int           asLongLongInt;
    unsigned long long int  asUnsignedLongLongInt;
    float                   asFloat;
    double                  asDouble;
    void*                   asPointer;
    const void*             asConstPointer;
    void(*asFunctionPointer());

    template<typename T>
    Variant( const T& value )
    {
      // FIXME sizeof( function pointer ) is not allowed
      PlatformSpecificMemCpy( this, &value, sizeof(T) );
    }
  } _variant;

};  // class Parameter


#endif /* TEST_DOUBLE_H */