/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "TracerTest.h"
#include <sk/runtime/Tracer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::runtime::test::TracerTest);

sk::runtime::test::TracerTest::
TracerTest()
{
}

sk::runtime::test::TracerTest::
~TracerTest()
{
}

void
sk::runtime::test::TracerTest::
setUp()
{
}

void
sk::runtime::test::TracerTest::
tearDown()
{
}

void
sk::runtime::test::TracerTest::
testCreate()
{
  Tracer tracer;
}
