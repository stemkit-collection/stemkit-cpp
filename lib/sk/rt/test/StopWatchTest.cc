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
#include <sk/rt/Thread.h>

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
  sk::rt::StopWatch stopwatch;

  CPPUNIT_ASSERT(stopwatch.isTicking() == false);

  stopwatch.stop();
  CPPUNIT_ASSERT(stopwatch.isTicking() == false);

  stopwatch.start();
  CPPUNIT_ASSERT(stopwatch.isTicking() == true);

  stopwatch.stop();
  CPPUNIT_ASSERT(stopwatch.isTicking() == false);
}

void 
sk::rt::test::StopWatchTest::
testNotStarted() 
{
  sk::rt::StopWatch stopwatch;

  CPPUNIT_ASSERT(stopwatch.isTicking() == false);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() == 0);

  stopwatch.stop();
  CPPUNIT_ASSERT(stopwatch.isTicking() == false);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() == 0);
}

void 
sk::rt::test::StopWatchTest::
testChangesUntilStopped()
{
  sk::rt::StopWatch stopwatch;

  stopwatch.start();
  CPPUNIT_ASSERT(stopwatch.isTicking() == true);

  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() != 0);

  uint64_t saved = stopwatch.getMilliseconds();

  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() > saved);

  saved = stopwatch.getMilliseconds();
  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() > saved);

  stopwatch.stop();
  saved = stopwatch.getMilliseconds();
  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT(stopwatch.getMilliseconds() == saved);
}

void 
sk::rt::test::StopWatchTest::
testInspect() 
{
  sk::rt::StopWatch stopwatch;
  CPPUNIT_ASSERT_EQUAL("<StopWatch: not started, 00:00:00.000>", stopwatch.inspect());

  stopwatch.start();
  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT_EQUAL("<StopWatch: running, 00:00:00.", stopwatch.inspect().substring(0, 30));

  stopwatch.stop();
  sk::rt::Thread::sleep(10);
  CPPUNIT_ASSERT_EQUAL("<StopWatch: stopped, 00:00:00.0" + sk::util::String::valueOf(stopwatch.getMilliseconds()) + '>', stopwatch.inspect());
}
