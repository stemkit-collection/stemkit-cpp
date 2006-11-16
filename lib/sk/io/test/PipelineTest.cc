/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipelineTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::PipelineTest);

sk::io::test::PipelineTest::
PipelineTest()
{
}

sk::io::test::PipelineTest::
~PipelineTest()
{
}

void
sk::io::test::PipelineTest::
setUp()
{
}

void
sk::io::test::PipelineTest::
tearDown()
{
}

void
sk::io::test::PipelineTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
