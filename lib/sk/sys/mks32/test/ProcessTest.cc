/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProcessTest.h"
#include <sk/sys/Process.h>
#include <sk/sys/AbstractProcessListener.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/util/Container.h>
#include <sk/util/UnsupportedOperationException.h>
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
  sk::sys::Process process(sk::util::StringArray("true"));
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
  sk::sys::Process process(sk::util::StringArray("false"));
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
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "exec sleep 60");
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  sleep(2);
  process.kill();
  process.join();

  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, process.isExited());
  CPPUNIT_ASSERT_EQUAL(true, process.isKilled());

  CPPUNIT_ASSERT_EQUAL(9, process.signal());
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

void
sk::sys::test::ProcessTest::
testRedirectInput()
{
  sk::io::AnonymousPipe pipe;
  sk::util::StringArray cmdline = sk::util::StringArray("sh") + "-c" + "read status; exit \"${status}\"";
  sk::sys::Process process(pipe.inputStream(), cmdline);
  pipe.inputStream().close();

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
  struct Worker : public sk::sys::AbstractProcessListener {
    Worker(sk::io::OutputStream& stream)
      : _stream(stream) {}

    void processStarting(sk::io::Stream& umbilical) {
      umbilical.close();
      _stream.close();

      int number;
      std::cin >> number ;

      _exit(number);
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

  CPPUNIT_ASSERT_THROW(sk::sys::Process(pipe.inputStream(), worker), sk::util::UnsupportedOperationException);
}

namespace {
  struct ConfiguringListener : public sk::sys::AbstractProcessListener {
    ConfiguringListener(sk::io::AnonymousPipe& pipe)
      : _pipe(pipe) {}

    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      configurator.setEnvironment("TESTCONFIGURING", "set from a process");
      configurator.setOutputStream(_pipe.outputStream());
    }
    sk::io::AnonymousPipe& _pipe;
  };
}

void
sk::sys::test::ProcessTest::
testConfiguring()
{
  CPPUNIT_ASSERT_EQUAL("", sk::util::String(getenv("TESTCONFIGURING")));

  sk::io::AnonymousPipe pipe;
  ConfiguringListener listener(pipe);
  sk::sys::Process process(sk::util::StringArray("sh") + "-c" + "echo E: ${TESTCONFIGURING}; sleep 60", listener);
  pipe.outputStream().close();

  sk::io::DataInputStream stream(pipe.inputStream());
  CPPUNIT_ASSERT_EQUAL("E: set from a process", stream.readLine().trim());
}
