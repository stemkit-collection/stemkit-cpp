/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "ReentrantLockTest.h"

#include <sk/util/SystemException.h>
#include <sk/util/Holder.cxx>
#include <sk/rt/ReentrantLock.h>
#include <sk/rt/Locker.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ReentrantLockTest);

sk::rt::thread::tests::ReentrantLockTest::
ReentrantLockTest()
{
}

sk::rt::thread::tests::ReentrantLockTest::
~ReentrantLockTest()
{
}

void
sk::rt::thread::tests::ReentrantLockTest::
setUp()
{
}

void
sk::rt::thread::tests::ReentrantLockTest::
tearDown()
{
  _lockHolder.clear();
}

void
sk::rt::thread::tests::ReentrantLockTest::
testLocking()
{
  sk::rt::ReentrantLock lock;
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(3, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getCounter());

  try {
    lock.unlock();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::Exception& exception) {
  }
}

namespace {
  struct Block {
    Block(const sk::rt::ReentrantLock& lock, bool& visited)
      : _lock(lock), _visited(visited) {}

    void operator()() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _lock.isLocked());
      CPPUNIT_ASSERT_EQUAL(1, _lock.getCounter());
    }

    const sk::rt::ReentrantLock& _lock;
    bool& _visited;
  };
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeFunctionObject()
{
  sk::rt::ReentrantLock lock;
  bool visited = false;

  CPPUNIT_ASSERT_EQUAL(false, visited);
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());

  Block b(lock, visited);

  (sk::rt::Locker(lock), b());
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, visited);

  visited = false;
  (sk::rt::Locker(lock), Block(lock, visited)());

  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, visited);
}

void
sk::rt::thread::tests::ReentrantLockTest::
criticalSectionWithoutParam()
{
  _visited = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeMethodWithoutParam()
{
  _visited = false;
  _lockHolder.set(new ReentrantLock);
  (sk::rt::Locker(_lockHolder.getMutable()), criticalSectionWithoutParam());

  CPPUNIT_ASSERT_EQUAL(true, _visited);
}

void
sk::rt::thread::tests::ReentrantLockTest::
constCriticalSectionWithoutParam() const
{
  _visited = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeConstMethodWithoutParam()
{
  _visited = false;
  _lockHolder.set(new ReentrantLock);
  (sk::rt::Locker(_lockHolder.getMutable()), constCriticalSectionWithoutParam());

  CPPUNIT_ASSERT_EQUAL(true, _visited);
}

void
sk::rt::thread::tests::ReentrantLockTest::
criticalSectionWithParam(bool& flag)
{
  flag = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeMethodWithParam()
{
  bool visited = false;
  _lockHolder.set(new ReentrantLock);
  (sk::rt::Locker(_lockHolder.getMutable()), criticalSectionWithParam(visited));

  CPPUNIT_ASSERT_EQUAL(true, visited);
}

void
sk::rt::thread::tests::ReentrantLockTest::
constCriticalSectionWithParam(bool& flag) const
{
  flag = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeConstMethodWithParam()
{
  bool visited = false;
  _lockHolder.set(new ReentrantLock);
  (sk::rt::Locker(_lockHolder.getMutable()), constCriticalSectionWithParam(visited));

  CPPUNIT_ASSERT_EQUAL(true, visited);
}

namespace {
  bool global_flag = false;
  void f() {
    global_flag = true;
  }
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeFunctionNamespace()
{
  global_flag = false;

  ReentrantLock lock;
  (sk::rt::Locker(lock), f());

  CPPUNIT_ASSERT_EQUAL(true, global_flag);
}

extern "C" {
  static bool global_c_flag = false;

  void cf() {
    global_c_flag = true;
  }
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeFunctionExternC()
{
  global_c_flag = false;

  ReentrantLock lock;
  (sk::rt::Locker(lock), cf());

  CPPUNIT_ASSERT_EQUAL(true, global_c_flag);
}

void
sk::rt::thread::tests::ReentrantLockTest::
testBasics()
{
  {
    sk::rt::ReentrantLock lock;
    lock.lock();
    lock.unlock();
  }
}
