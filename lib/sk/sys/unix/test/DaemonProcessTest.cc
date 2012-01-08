/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "DaemonProcessTest.h"
#include <sk/sys/DaemonProcess.h>
#include <sk/sys/ProcessLaunchException.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/io/DataInputStream.h>
#include "../ManagedProcess.h"

#include <signal.h>
#include <errno.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::DaemonProcessTest);

sk::sys::test::DaemonProcessTest::
DaemonProcessTest()
{
}

sk::sys::test::DaemonProcessTest::
~DaemonProcessTest()
{
}

void
sk::sys::test::DaemonProcessTest::
setUp()
{
}

void
sk::sys::test::DaemonProcessTest::
tearDown()
{
}

void
sk::sys::test::DaemonProcessTest::
testStartStop()
{
  sk::sys::DaemonProcess process(sk::util::Strings("sleep") << "3600");
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());

  process.start();
  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());

  process.stop();
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
}

void
sk::sys::test::DaemonProcessTest::
testDestroyKillsProcess()
{
  int pid;
  {
    sk::sys::DaemonProcess process(sk::util::Strings("sleep") << "3600");
    CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
    process.start();

    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
    pid = process.getPid();
    CPPUNIT_ASSERT(::kill(pid, 0) == 0);
  }
  CPPUNIT_ASSERT(::kill(pid, 0) != 0);
  CPPUNIT_ASSERT_EQUAL(ESRCH, errno);
}

void
sk::sys::test::DaemonProcessTest::
testDestroyLeavesProcessWhenStartedDetached()
{
  int pid;
  {
    sk::sys::DaemonProcess process(sk::util::Strings("sleep") << "3600");
    CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
    process.startDetached();

    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
    pid = process.getPid();
  }
  sk::sys::ManagedProcess process(pid);
  try {
    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
  }
  catch(...) {
    try {
      process.stop();
    }
    catch(...) {}
    throw;
  }
  process.stop();
}

void
sk::sys::test::DaemonProcessTest::
testDestroyLeavesProcessWhenExplicitlyDetached()
{
  int pid;
  {
    sk::sys::DaemonProcess process(sk::util::Strings("sleep") << "3600");
    CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
    process.start();

    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
    pid = process.getPid();
    process.detach();
  }
  sk::sys::ManagedProcess process(pid);
  try {
    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
  }
  catch(...) {
    try {
      process.stop();
    }
    catch(...) {}
    throw;
  }
  process.stop();
}

void
sk::sys::test::DaemonProcessTest::
testFailedCommand()
{
  sk::sys::DaemonProcess process(sk::util::Strings("/zzz/bbb"));
  CPPUNIT_ASSERT_THROW(process.start(), sk::sys::ProcessLaunchException);
}

namespace {
  struct TalkingDaemonProcess : public sk::sys::DaemonProcess {
    TalkingDaemonProcess(const sk::util::Strings& cmdline)
      : sk::sys::DaemonProcess(cmdline) {}

    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      sk::sys::DaemonProcess::processConfiguring(configurator);
      configurator.addStream(pipe.outputStream());
    }
    sk::io::AnonymousPipe pipe;
  };
}

void
sk::sys::test::DaemonProcessTest::
testStreamCommunication()
{
  TalkingDaemonProcess process(sk::util::Strings("ruby") + "-e" + "IO.new(ENV['SK_STREAMS'].to_i).puts :HELLO");
  process.start();

  process.pipe.outputStream().close();
  sk::io::DataInputStream stream(process.pipe.inputStream());

  CPPUNIT_ASSERT_EQUAL("HELLO", stream.readLine().trim());
}
