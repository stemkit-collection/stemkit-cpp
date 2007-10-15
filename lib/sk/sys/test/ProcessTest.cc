/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProcessTest.h"
#include <sk/sys/Process.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/util/Container.h>
#include <iostream>

#include <signal.h>
#include <unistd.h>

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
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "kill -9 ${$}; exec sleep 2");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(SIGKILL, process.signal());
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

namespace {
  struct Cleaner : public virtual sk::sys::ProcessListener {
    Cleaner(sk::io::OutputStream& stream)
      : _stream(stream) {}

    void processStarting() {
      _stream.close();
    }
    int processStopping() {
      return 0;
    }
    void processJoining() {
    }
    sk::io::OutputStream& _stream;
  };
}

void
sk::sys::test::ProcessTest::
testRedirectInput()
{
  sk::io::AnonymousPipe pipe;
  sk::util::StringArray cmdline = sk::util::StringArray("sh") + "-c" + "read status; exit \"${status}\"";
  Cleaner cleaner(pipe.outputStream());

  sk::sys::Process process(pipe.inputStream(), cmdline, cleaner);
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  pipe.outputStream().write(sk::util::Container("71"));
  pipe.outputStream().close();

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(71, process.exitStatus());
}

void
sk::sys::test::ProcessTest::
testNoHangOnInputRead()
{
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "read line");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.join();
  CPPUNIT_ASSERT_EQUAL(false, process.isSuccess());
}

namespace {
  struct Worker : public virtual sk::sys::ProcessListener {
    Worker(sk::io::OutputStream& stream)
      : _stream(stream) {}

    void processStarting() {
      _stream.close();

      int number;
      std::cin >> number ;

      _exit(number);
    }
    int processStopping() {
      return 0;
    }
    void processJoining() {
    }
    sk::io::OutputStream& _stream;
  };
}

void
sk::sys::test::ProcessTest::
testSpawn()
{
  sk::io::AnonymousPipe pipe;
  Worker worker(pipe.outputStream());

  sk::sys::Process process(pipe.inputStream(), worker);
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  pipe.outputStream().write(sk::util::Container("84"));
  pipe.outputStream().close();

  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, process.isExited());
  CPPUNIT_ASSERT_EQUAL(false, process.isKilled());
  CPPUNIT_ASSERT_EQUAL(84, process.exitStatus());
}

