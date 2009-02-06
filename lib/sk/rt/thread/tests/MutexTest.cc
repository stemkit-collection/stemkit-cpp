/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "MutexTest.h"
#include <sk/rt/thread/Mutex.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::MutexTest);

sk::rt::thread::tests::MutexTest::
MutexTest()
{
}

sk::rt::thread::tests::MutexTest::
~MutexTest()
{
}

void
sk::rt::thread::tests::MutexTest::
setUp()
{
}

void
sk::rt::thread::tests::MutexTest::
tearDown()
{
}

void
sk::rt::thread::tests::MutexTest::
testCreate()
{
  sk::rt::thread::Mutex mutex;
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
}
