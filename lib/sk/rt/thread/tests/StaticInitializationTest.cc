/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "StaticInitializationTest.h"
#include <sk/rt/Mutex.h>
#include <sk/rt/Locker.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::StaticInitializationTest);

static sk::rt::Mutex _mutex;

sk::rt::thread::tests::StaticInitializationTest::
StaticInitializationTest()
{
}

sk::rt::thread::tests::StaticInitializationTest::
~StaticInitializationTest()
{
}

void
sk::rt::thread::tests::StaticInitializationTest::
setUp()
{
}

void
sk::rt::thread::tests::StaticInitializationTest::
tearDown()
{
}

void
sk::rt::thread::tests::StaticInitializationTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL(false, _mutex.isLocked());
  {
    sk::rt::Locker locker(_mutex);
    CPPUNIT_ASSERT_EQUAL(true, _mutex.isLocked());
  }
  CPPUNIT_ASSERT_EQUAL(false, _mutex.isLocked());
}
