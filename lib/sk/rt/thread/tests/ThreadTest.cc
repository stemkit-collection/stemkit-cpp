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
  CPPUNIT_ASSERT(thread.getState() == sk::rt::thread::State::SK_T_NEW);

  CPPUNIT_ASSERT_EQUAL(false, thread.isAlive());
  CPPUNIT_ASSERT_EQUAL(true, thread.isRegular());
  CPPUNIT_ASSERT_EQUAL(false, thread.isMain());
  CPPUNIT_ASSERT_EQUAL(false, thread.isService());
  CPPUNIT_ASSERT_EQUAL(false, thread.isDetached());
}

void 
sk::rt::thread::tests::ThreadTest::
testMain()
{
  sk::rt::thread::Generic& current = Thread::currentThread();
  CPPUNIT_ASSERT_EQUAL("Main", current.getName());
  CPPUNIT_ASSERT(current.getState() == sk::rt::thread::State::SK_T_RUNNABLE);

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
