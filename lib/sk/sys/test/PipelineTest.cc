/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipelineTest.h"
#include <sk/sys/Pipeline.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::PipelineTest);

sk::sys::test::PipelineTest::
PipelineTest()
{
}

sk::sys::test::PipelineTest::
~PipelineTest()
{
}

void
sk::sys::test::PipelineTest::
setUp()
{
}

void
sk::sys::test::PipelineTest::
tearDown()
{
}

void
sk::sys::test::PipelineTest::
testCreate()
{
  Pipeline pipe;
}
