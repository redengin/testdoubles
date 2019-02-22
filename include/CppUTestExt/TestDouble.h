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

#include <CppUTest/SimpleString.h>
#include <CppUTestExt/TestDoubleParameter.h>

void failUnexpected( bool mode = true );
void checkExpectations();



// Expectation framework
class ExpectedCall;
class ActualCall;
namespace TestDouble {

// list of expectations
class ExpectationChain
{
public:
  const ExpectedCall* const pExpectedCall;
  int                       calledCount;
  ExpectationChain*         pNext;

  ExpectationChain( const ExpectedCall* const _pExpectedCall, ExpectationChain* const pLast );
  ~ExpectationChain();
};

class ExpectationQueue
{
public:
  ExpectationQueue();
  ~ExpectationQueue();

  void enqueue( const ExpectedCall* pCall );
  void check();
private:
  ExpectationChain*   _pExpectations;
  ExpectationChain*   _pLastExpectation;
};
static ExpectationQueue expectations;

// Expectation* findExpectation( const ActualCall& call );
ExpectedCall* findExpectation( const ActualCall& call );


// generic list of parameters (used for both input and output)
struct ParameterChain
{
  const TestDouble::Parameter* const pParameter;
  ParameterChain* const pNext;

  ParameterChain( const TestDouble::Parameter* const _pParameter, ParameterChain* const _pNext );
  ~ParameterChain();
};

} // namespace TestDouble

#endif /* TEST_DOUBLE_H */
