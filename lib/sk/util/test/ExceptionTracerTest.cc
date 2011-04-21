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
  struct TraceProducer : public virtual sk::util::exception::trace::Producer {
    void setup() {
    }

    const sk::util::String produceTrace() {
      return "<sample trace output>";
    }

    void reset() {
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
}

void
sk::util::test::ExceptionTracerTest::
tearDown()
{
  sk::util::exception::Tracer::clearProducerFactory();
}

void
sk::util::test::ExceptionTracerTest::
testBasics()
{
  sk::util::IllegalStateException exception("abcd");
  CPPUNIT_ASSERT_EQUAL("<sample trace output>", exception.getTrace());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abcd\n<sample trace output>", exception.what());
}
