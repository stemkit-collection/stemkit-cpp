/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "SingularMutexTest.h"
#include "../Mutex.h"
#include "../Exception.h"
#include <sk/util/Holder.cxx>
#include <errno.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::pthreads::tests::SingularMutexTest);

sk::rt::thread::pthreads::tests::SingularMutexTest::
SingularMutexTest()
  : _scope("sk::rt::thread::pthreads")
{
}

sk::rt::thread::pthreads::tests::SingularMutexTest::
~SingularMutexTest()
{
}

void
sk::rt::thread::pthreads::tests::SingularMutexTest::
setUp()
{
}

void
sk::rt::thread::pthreads::tests::SingularMutexTest::
tearDown()
{
}

void
sk::rt::thread::pthreads::tests::SingularMutexTest::
testUnlockFailsOnNonLocked()
{
  sk::util::Holder<Mutex> _mutexHolder(pthreads::Mutex::makeSingular(_scope));
  try {
    _mutexHolder.getMutable().unlock();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const pthreads::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("pthread_mutex_unlock", exception.getFunctionName());
    CPPUNIT_ASSERT_EQUAL(uint32_t(EPERM), exception.getCode());
  }
}

void
sk::rt::thread::pthreads::tests::SingularMutexTest::
testLockUnlock()
{
  sk::util::Holder<Mutex> _mutexHolder(pthreads::Mutex::makeSingular(_scope));
  CPPUNIT_ASSERT_THROW(_mutexHolder.getMutable().unlock(), sk::rt::thread::pthreads::Exception);

  CPPUNIT_ASSERT_NO_THROW(_mutexHolder.getMutable().lock());
  CPPUNIT_ASSERT_THROW(_mutexHolder.getMutable().lock(), sk::rt::thread::pthreads::Exception);

  CPPUNIT_ASSERT_NO_THROW(_mutexHolder.getMutable().unlock());
  CPPUNIT_ASSERT_THROW(_mutexHolder.getMutable().unlock(), sk::rt::thread::pthreads::Exception);
}

void
sk::rt::thread::pthreads::tests::SingularMutexTest::
testTryLock()
{
  sk::util::Holder<Mutex> _mutexHolder(pthreads::Mutex::makeSingular(_scope));

  CPPUNIT_ASSERT(_mutexHolder.getMutable().tryLock() == true);
  CPPUNIT_ASSERT(_mutexHolder.getMutable().tryLock() == false);
  CPPUNIT_ASSERT_THROW(_mutexHolder.getMutable().lock(), sk::rt::thread::pthreads::Exception);

  CPPUNIT_ASSERT_NO_THROW(_mutexHolder.getMutable().unlock());
  CPPUNIT_ASSERT_THROW(_mutexHolder.getMutable().unlock(), sk::rt::thread::pthreads::Exception);
}
