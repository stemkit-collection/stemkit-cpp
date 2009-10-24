/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "TimerTest.h"
#include <sk/rt/Timer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::test::TimerTest);

sk::rt::test::TimerTest::
TimerTest()
{
}

sk::rt::test::TimerTest::
~TimerTest()
{
}

void
sk::rt::test::TimerTest::
setUp()
{
}

void
sk::rt::test::TimerTest::
tearDown()
{
}

void
sk::rt::test::TimerTest::
testTicking()
{
  sk::rt::Timer timer;

  CPPUNIT_ASSERT(timer.isTicking() == false);

  timer.stop();
  CPPUNIT_ASSERT(timer.isTicking() == false);

  timer.start();
  CPPUNIT_ASSERT(timer.isTicking() == true);

  timer.stop();
  CPPUNIT_ASSERT(timer.isTicking() == false);
}
