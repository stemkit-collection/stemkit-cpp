/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProcessTest.h"
#include <sk/io/Process.h>
#include <sk/io/AnonymousPipe.h>

#include <signal.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::ProcessTest);

sk::io::test::ProcessTest::
ProcessTest()
{
}

sk::io::test::ProcessTest::
~ProcessTest()
{
}

void
sk::io::test::ProcessTest::
setUp()
{
}

void
sk::io::test::ProcessTest::
tearDown()
{
}

void
sk::io::test::ProcessTest::
testTrueCommand()
{
  sk::io::Process process("true");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(0, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(true, process.isSuccess());
}

void
sk::io::test::ProcessTest::
testFalseCommand()
{
  sk::io::Process process("false");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(1, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}

void
sk::io::test::ProcessTest::
testExitCode()
{
  sk::io::Process process(sk::util::StringArray("sh") + "-c" + "exit 5");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(5, process.exitStatus());
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}

void
sk::io::test::ProcessTest::
testKilled()
{
  sk::io::Process process(sk::util::StringArray("sh") + "-c" + "kill ${$}; sleep(60)");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGTERM, process.signal());
}

void
sk::io::test::ProcessTest::
testNormalStop()
{
  sk::io::Process process(sk::util::StringArray("sh") + "-c" + "sleep(60)");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.stop();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGTERM, process.signal());
}

void
sk::io::test::ProcessTest::
testForcedStop()
{
  sk::io::Process process(sk::util::StringArray("sh") + "-c" + "trap '' 2; sleep(60)");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.stop();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGKILL, process.signal());
}
