/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProcessTest.h"
#include <sk/sys/Process.h>
#include <sk/io/AnonymousPipe.h>

#include <signal.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::ProcessTest);

sk::sys::test::ProcessTest::
ProcessTest()
{
}

sk::sys::test::ProcessTest::
~ProcessTest()
{
}

void
sk::sys::test::ProcessTest::
setUp()
{
}

void
sk::sys::test::ProcessTest::
tearDown()
{
}

void
sk::sys::test::ProcessTest::
testTrueCommand()
{
  sk::sys::Process process("true");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(0, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::sys::test::ProcessTest::
testFalseCommand()
{
  sk::sys::Process process("false");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(1, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}

void
sk::sys::test::ProcessTest::
testExitCode()
{
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "exit 5");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(5, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}

void
sk::sys::test::ProcessTest::
testKilled()
{
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "kill ${$}; exec sleep 2");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGTERM, process.signal());
}

void
sk::sys::test::ProcessTest::
testNormalStop()
{
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "exec sleep 10");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sleep(1);
  process.stop();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGTERM, process.signal());
}

void
sk::sys::test::ProcessTest::
testForcedStop()
{
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "trap '' 15; exec sleep 10");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sleep(1);
  process.stop();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGKILL, process.signal());
}
