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
#include <sk/util/ArrayList.cxx>

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
    Block(const sk::util::String& message, sk::rt::Lock& lock)
      : _message(message), _lock(lock) {}

    void run() {
      while(true) {
        _lock.synchronize(*this, &Block::tick);
        sk::rt::Thread::sleep(2000);
      }
    }

    void tick() const {
      sk::rt::thread::Generic& current = sk::rt::Thread::currentThread();
      std::cerr << "TICK: " 
        << current.inspect() << ": "
        << _message.inspect() << ", " << _lock.inspect()
      << std::endl;
    }
    sk::rt::Lock& _lock;
    const sk::util::String _message;
  };
}

namespace {
  struct Starter : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.start();
      sk::rt::Thread::sleep(1000);
    }
  };
  struct Joiner : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.join();
    }
  };
}

void
sk::rt::thread::tests::ThreadOperationTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL(true, Thread::currentThread().isMain());

  ReentrantLock lock;
  util::ArrayList<Thread> threads;

  threads.add(new Thread(new Block("aaa", lock)));
  threads.add(new Thread(new Block("bbb", lock)));
  threads.add(new Thread(new Block("ccc", lock)));
  threads.add(new Thread(new Block("ccc", lock)));
  threads.add(new Thread(new Block("ccc", lock)));
  threads.add(new Thread(new Block("ccc", lock)));

  threads.forEach(Starter());
  threads.forEach(Joiner());
}

