/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ThreadOperationTest.h"

#include <sk/rt/Thread.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/ReentrantLock.h>

#include <unistd.h>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ThreadOperationTest);

sk::rt::thread::tests::ThreadOperationTest::
ThreadOperationTest()
{
}

sk::rt::thread::tests::ThreadOperationTest::
~ThreadOperationTest()
{
}

void
sk::rt::thread::tests::ThreadOperationTest::
setUp()
{
}

void
sk::rt::thread::tests::ThreadOperationTest::
tearDown()
{
  Thread::reset();
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block(const sk::util::String& message)
      : _message(message) {}

    void run() const {
      sk::rt::thread::Generic& current = sk::rt::Thread::currentThread();
      for(int counter=3; counter > 0 ;--counter) {
        _lock.lock();
        std::cerr << "TICK: " 
          << current.getName() << ": "
          << std::boolalpha << current.isMain() << ": "
          << _message.inspect() << ", " << _lock.inspect()
        << std::endl;

        sk::rt::Thread::sleep(2000);
      }
      _lock.unlock();
      _lock.unlock();
      _lock.unlock();
    }
    mutable sk::rt::ReentrantLock _lock;
    const sk::util::String _message;
  };
}

void
sk::rt::thread::tests::ThreadOperationTest::
testBasics()
{
  Block b1("aaa");
  Block b2("bbb");

  Thread t1(b1);
  Thread t2(b2);

  t1.start();
  Thread::sleep(1000);
  t2.start();

  t1.join();
  t2.join();
}

void 
sk::rt::thread::tests::ThreadOperationTest::
testMainThread()
{
  sk::rt::thread::Generic& current = Thread::currentThread();

  CPPUNIT_ASSERT_EQUAL(true, current.isMain());
  CPPUNIT_ASSERT_EQUAL(false, current.isService());
  CPPUNIT_ASSERT_EQUAL(false, current.isRegular());
  CPPUNIT_ASSERT_EQUAL(true, current.isAlive());
}
