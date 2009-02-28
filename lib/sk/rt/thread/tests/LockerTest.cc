/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "LockerTest.h"
#include <sk/util/Holder.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::LockerTest);

sk::rt::thread::tests::LockerTest::
LockerTest()
{
}

sk::rt::thread::tests::LockerTest::
~LockerTest()
{
}

void
sk::rt::thread::tests::LockerTest::
setUp()
{
}

void
sk::rt::thread::tests::LockerTest::
tearDown()
{
}

void
sk::rt::thread::tests::LockerTest::
testStatementScope()
{
  sk::rt::Mutex mutex;

  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  (sk::rt::Locker(mutex), CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked()));
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
}

void
sk::rt::thread::tests::LockerTest::
testBlockScope()
{
  sk::rt::Mutex mutex;
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  {
    const Locker locker(mutex);
    CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());
  }
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
}

void 
sk::rt::thread::tests::LockerTest::
testCopying()
{
  sk::rt::Mutex mutex;
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  {
    const Locker locker(mutex);
    CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());

    Locker another(locker);
    CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());

    Locker yet_another(locker);
    CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());

    Locker other_another(another);
    CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());
  }
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
}

const sk::rt::Locker 
sk::rt::thread::tests::LockerTest::
locker_originator()
{
  return Locker(_mutexHolder.get());
}

void
sk::rt::thread::tests::LockerTest::
testReturning()
{
  _mutexHolder.set(new Mutex);
  CPPUNIT_ASSERT_EQUAL(false, _mutexHolder.get().isLocked());
  {
    sk::rt::Locker locker = locker_originator();
    CPPUNIT_ASSERT_EQUAL(true, _mutexHolder.get().isLocked());
  }
  CPPUNIT_ASSERT_EQUAL(false, _mutexHolder.get().isLocked());
}

void
sk::rt::thread::tests::LockerTest::
locker_pitcher()
{
  throw sk::rt::Locker(_mutexHolder.get());
}

void
sk::rt::thread::tests::LockerTest::
testThrowing()
{
  _mutexHolder.set(new Mutex);
  CPPUNIT_ASSERT_EQUAL(false, _mutexHolder.get().isLocked());

  try {
    locker_pitcher();
    CPPUNIT_FAIL("Must not get here");
  }
  catch(const sk::rt::Locker& locker) {
    CPPUNIT_ASSERT_EQUAL(true, _mutexHolder.get().isLocked());
  }
  CPPUNIT_ASSERT_EQUAL(false, _mutexHolder.get().isLocked());
}
