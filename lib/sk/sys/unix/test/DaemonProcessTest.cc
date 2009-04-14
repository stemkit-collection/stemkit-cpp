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
  sk::sys::DaemonProcess process(sk::util::StringArray("sleep") << "3600");
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
    sk::sys::DaemonProcess process(sk::util::StringArray("sleep") << "3600");
    CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
    process.start();

    CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
    pid = process.getPid();
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
    sk::sys::DaemonProcess process(sk::util::StringArray("sleep") << "3600");
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
    sk::sys::DaemonProcess process(sk::util::StringArray("sleep") << "3600");
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
