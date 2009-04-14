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
testBasics()
{
  sk::sys::DaemonProcess process(sk::util::StringArray("sleep") << "3600");
  CPPUNIT_ASSERT_EQUAL(false, process.isAlive());
  process.start();

  CPPUNIT_ASSERT_EQUAL(true, process.isAlive());
}
