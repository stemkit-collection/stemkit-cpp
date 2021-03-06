/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/


#include <sk/util/IllegalStateException.h>
#include "CriticalSectionTest.h"
#include "..\CriticalSection.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::win32::tests::CriticalSectionTest);

sk::rt::thread::win32::tests::CriticalSectionTest::
CriticalSectionTest()
{
}

sk::rt::thread::win32::tests::CriticalSectionTest::
~CriticalSectionTest()
{
}

void
sk::rt::thread::win32::tests::CriticalSectionTest::
setUp()
{
}

void
sk::rt::thread::win32::tests::CriticalSectionTest::
tearDown()
{
}

void
sk::rt::thread::win32::tests::CriticalSectionTest::
testBasics()
{
  win32::CriticalSection section;

  CPPUNIT_ASSERT_EQUAL(true, section.hasEnterCount());
  CPPUNIT_ASSERT_EQUAL(0, section.getEnterCount());

  section.lock();
  CPPUNIT_ASSERT_EQUAL(1, section.getEnterCount());

  section.lock();
  CPPUNIT_ASSERT_EQUAL(2, section.getEnterCount());

  section.unlock();
  section.unlock();

  CPPUNIT_ASSERT_EQUAL(0, section.getEnterCount());
}

void
sk::rt::thread::win32::tests::CriticalSectionTest::
testUnlockingNotLockedFails()
{
  win32::CriticalSection section;
  CPPUNIT_ASSERT_THROW(section.unlock(), sk::util::IllegalStateException);
}

void 
sk::rt::thread::win32::tests::CriticalSectionTest::
testEnterLimit()
{
  win32::CriticalSection section;
  section.setDepth(1);

  CPPUNIT_ASSERT_EQUAL(0, section.getEnterCount());
  section.lock();
  CPPUNIT_ASSERT_EQUAL(1, section.getEnterCount());

  try {
    section.lock();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::IllegalStateException& exception) {
    CPPUNIT_ASSERT_EQUAL(1, section.getEnterCount());
  }
}
