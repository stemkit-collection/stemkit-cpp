/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "StopWatchTest.h"
#include <sk/rt/StopWatch.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::test::StopWatchTest);

sk::rt::test::StopWatchTest::
StopWatchTest()
{
}

sk::rt::test::StopWatchTest::
~StopWatchTest()
{
}

void
sk::rt::test::StopWatchTest::
setUp()
{
}

void
sk::rt::test::StopWatchTest::
tearDown()
{
}

void
sk::rt::test::StopWatchTest::
testTicking()
{
  sk::rt::StopWatch timer;

  CPPUNIT_ASSERT(timer.isTicking() == false);

  timer.stop();
  CPPUNIT_ASSERT(timer.isTicking() == false);

  timer.start();
  CPPUNIT_ASSERT(timer.isTicking() == true);

  timer.stop();
  CPPUNIT_ASSERT(timer.isTicking() == false);
}
