/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "ThreadTest.h"
#include "DataGenerator.h"
#include <sk/util/ArrayList.cxx>

#include <sk/rt/Thread.h>
#include <sk/util/IllegalStateException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ThreadTest);

sk::rt::thread::tests::ThreadTest::
ThreadTest()
{
}

sk::rt::thread::tests::ThreadTest::
~ThreadTest()
{
}

void
sk::rt::thread::tests::ThreadTest::
setUp()
{
  sk::rt::Thread::reset();
}

void
sk::rt::thread::tests::ThreadTest::
tearDown()
{
  sk::rt::Thread::reset();
}

void
sk::rt::thread::tests::ThreadTest::
testCreateRegular()
{
  sk::rt::Thread thread;

  CPPUNIT_ASSERT_EQUAL("Thread-1", thread.getName());
  CPPUNIT_ASSERT_EQUAL(sk::rt::thread::State::SK_T_NEW, thread.getState());
  CPPUNIT_ASSERT_EQUAL("<sk::rt::Thread: name=\"Thread-1\", id=1, main?=false, detached?=false, state=NEW>", thread.inspect());

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, thread.isRegular());
  CPPUNIT_ASSERT_EQUAL(false, thread.isMain());
  CPPUNIT_ASSERT_EQUAL(false, thread.isService());
  CPPUNIT_ASSERT_EQUAL(false, thread.isDetached());
  CPPUNIT_ASSERT_EQUAL(false, thread.isExited());
  CPPUNIT_ASSERT_EQUAL(false, thread.isInterrupted());
  CPPUNIT_ASSERT_EQUAL(false, thread.isException());

  CPPUNIT_ASSERT_THROW(thread.exitStatus(), sk::util::IllegalStateException);
}

void 
sk::rt::thread::tests::ThreadTest::
testMain()
{
  sk::rt::thread::Generic& current = Thread::currentThread();
  CPPUNIT_ASSERT_EQUAL("Main", current.getName());
  CPPUNIT_ASSERT_EQUAL(sk::rt::thread::State::SK_T_RUNNING, current.getState());
  CPPUNIT_ASSERT_EQUAL("<sk::rt::thread::Main: name=\"Main\", id=0, main?=true, detached?=false, state=RUNNING>", current.inspect());

  CPPUNIT_ASSERT_EQUAL(true, current.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, current.isMain());
  CPPUNIT_ASSERT_EQUAL(false, current.isService());
  CPPUNIT_ASSERT_EQUAL(false, current.isRegular());
  CPPUNIT_ASSERT_EQUAL(false, current.isDetached());
  CPPUNIT_ASSERT_EQUAL(false, current.isExited());
  CPPUNIT_ASSERT_EQUAL(false, current.isInterrupted());
  CPPUNIT_ASSERT_EQUAL(false, current.isException());

  CPPUNIT_ASSERT_THROW(current.exitStatus(), sk::util::IllegalStateException);
}

void
sk::rt::thread::tests::ThreadTest::
testDataGeneration()
{
  std::vector<int> basket;
  int threads = 20;
  int amount = 1000;
  int runs = 7;
  DataGenerator generator(threads, basket);

  generator.fill(amount, runs);

  CPPUNIT_ASSERT_EQUAL(size_t(threads * amount * runs), basket.size());

  int blocks = threads * runs;
  for(int block=0; block < blocks ;++block) {
    int base = block * amount;
    for(int counter=1; counter<amount ;++counter) {
      CPPUNIT_ASSERT_EQUAL(basket.at(base + 0), basket.at(base + counter));
    }
  }
}

void
sk::rt::thread::tests::ThreadTest::
testJoiningNotStartedFails()
{
  Thread thread;
  CPPUNIT_ASSERT_THROW(thread.join(), sk::util::IllegalStateException);
}

void
sk::rt::thread::tests::ThreadTest::
testDefaultRunSucceeds()
{
  Thread thread;

  CPPUNIT_ASSERT_NO_THROW(thread.start());
  CPPUNIT_ASSERT_NO_THROW(thread.join());

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, thread.isInterrupted());
  CPPUNIT_ASSERT_EQUAL(false, thread.isException());
  CPPUNIT_ASSERT_EQUAL(true, thread.isExited());
  CPPUNIT_ASSERT_EQUAL(0, thread.exitStatus());
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block() 
      : exitCode(-1) {}

    void run() {
      while(true) {
        sk::rt::Thread::sleep(500);
        if(exitCode != -1) {
          throw sk::rt::thread::Exit(exitCode);
        }
        if(sk::rt::Thread::currentThread().isInterrupted() == true) {
          throw sk::rt::thread::Exit(-4);
        }
      }
    }
    volatile int exitCode;
  };
};

void 
sk::rt::thread::tests::ThreadTest::
testStartStop()
{
  Thread thread(new Block);

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(sk::rt::thread::State::SK_T_NEW, thread.getState());

  CPPUNIT_ASSERT_NO_THROW(thread.start());
  Thread::sleep(100);
  CPPUNIT_ASSERT_EQUAL(true, thread.isAlive());
  CPPUNIT_ASSERT_NO_THROW(thread.stop());

  thread.join();

  CPPUNIT_ASSERT_EQUAL(sk::rt::thread::State::SK_T_STOPPED, thread.getState());
}

void
sk::rt::thread::tests::ThreadTest::
testExitWithStatus()
{
  Block block;
  Thread thread(block);

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  thread.start();
  Thread::sleep(100);
  CPPUNIT_ASSERT_EQUAL(true, thread.isAlive());

  block.exitCode = 12;
  thread.join();

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, thread.isExited());
  CPPUNIT_ASSERT_EQUAL(12, thread.exitStatus());
}

void
sk::rt::thread::tests::ThreadTest::
testInterrupting()
{
  Thread thread(new Block);

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  thread.start();
  Thread::sleep(1000);
  CPPUNIT_ASSERT_EQUAL(true, thread.isAlive());

  thread.interrupt();
  thread.join();

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, thread.isExited());
  CPPUNIT_ASSERT_EQUAL(-4, thread.exitStatus());
}

void
sk::rt::thread::tests::ThreadTest::
testDetaching()
{
  Thread thread(new Block());

  CPPUNIT_ASSERT_EQUAL(false, thread.isDetached());
  CPPUNIT_ASSERT_THROW(thread.detach(), sk::util::IllegalStateException);

  thread.start();
  Thread::sleep(1000);

  CPPUNIT_ASSERT_EQUAL(true, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(false, thread.isDetached());

  thread.detach();
  CPPUNIT_ASSERT_EQUAL(true, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, thread.isDetached());

  thread.stop();
  Thread::sleep(1);
  CPPUNIT_ASSERT_EQUAL(thread::State::SK_T_STOPPED, thread.getState());
}
