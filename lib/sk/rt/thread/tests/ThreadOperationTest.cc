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
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block(const sk::util::String& message)
      : _message(message) {}

    void run() const {
      for(int counter=5; counter > 0 ;--counter) {
        std::cerr << "TICK: " << _message.inspect() << std::endl;
        sleep(10);
      }
    }
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
  sleep(5);
  t2.start();

  t1.join();
  t2.join();
}
