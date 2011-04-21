/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ExceptionTracerTest.h"
#include <sk/util/exception/Tracer.h>
#include <sk/util/exception/trace/Producer.h>
#include <sk/util/IllegalStateException.h>
#include <stdexcept>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ExceptionTracerTest);

sk::util::test::ExceptionTracerTest::
ExceptionTracerTest()
{
}

sk::util::test::ExceptionTracerTest::
~ExceptionTracerTest()
{
}

namespace {
  bool raiseSetupException = false;
  bool raiseResetException = false;
  bool raiseProduceException = false;

  struct TraceProducer : public virtual sk::util::exception::trace::Producer {
    void setup() {
      if(raiseSetupException == true) {
        throw std::domain_error("setup error");
      }
    }

    const sk::util::String produceTrace() {
      if(raiseProduceException == true) {
        throw std::domain_error("produce error");
      }
      return "<sample trace output>";
    }

    void reset() {
      if(raiseResetException == true) {
        throw std::domain_error("reset error");
      }
    }
  };
}

sk::util::exception::trace::Producer* 
sk::util::test::ExceptionTracerTest::
createTraceProducer() const
{
  return new TraceProducer();
}

void
sk::util::test::ExceptionTracerTest::
setUp()
{
  sk::util::exception::Tracer::setProducerFactory(*this);

  raiseSetupException = false;
  raiseResetException = false;
  raiseProduceException = false;
}

void
sk::util::test::ExceptionTracerTest::
tearDown()
{
  sk::util::exception::Tracer::clearProducerFactory();
}

void
sk::util::test::ExceptionTracerTest::
test_trace_produced_normally()
{
  sk::util::IllegalStateException exception("abcd");
  CPPUNIT_ASSERT_EQUAL("<sample trace output>", exception.getTrace());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abcd\n<sample trace output>", exception.what());
}

void
sk::util::test::ExceptionTracerTest::
test_trace_errors_in_setup()
{
  raiseSetupException = true;

  sk::util::IllegalStateException exception("abcd");
  CPPUNIT_ASSERT_EQUAL("<Error in trace setup: setup error>", exception.getTrace());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abcd\n<Error in trace setup: setup error>", exception.what());
}

void
sk::util::test::ExceptionTracerTest::
test_trace_errors_in_reset()
{
  raiseResetException = true;

  sk::util::IllegalStateException exception("abcd");
  CPPUNIT_ASSERT_EQUAL("<sample trace output><Error in trace reset: reset error>", exception.getTrace());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abcd\n<sample trace output><Error in trace reset: reset error>", exception.what());
}

void
sk::util::test::ExceptionTracerTest::
test_trace_errors_in_produce()
{
  raiseProduceException = true;

  sk::util::IllegalStateException exception("abcd");
  CPPUNIT_ASSERT_EQUAL("<Error in trace produce: produce error>", exception.getTrace());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abcd\n<Error in trace produce: produce error>", exception.what());
}

