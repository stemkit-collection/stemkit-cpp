/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "HolderTest.h"
#include <sk/util/Holder.h>
#include <sk/util/MissingResourceException.h>
#include <sk/util/UnsupportedOperationException.h>
#include "Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::HolderTest);

sk::util::test::HolderTest::
HolderTest()
{
}

sk::util::test::HolderTest::
~HolderTest()
{
}

void
sk::util::test::HolderTest::
setUp()
{
  Probe::resetCounter();
}

void
sk::util::test::HolderTest::
tearDown()
{
  Probe::resetCounter();
}

void
sk::util::test::HolderTest::
testCreateWithReference()
{
  Probe probe("abc");
  Holder<Probe> holder(probe);

  CPPUNIT_ASSERT_EQUAL(&probe, &holder.get());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.contains(probe));
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));
}

void
sk::util::test::HolderTest::
testCreateWithPointer()
{
  Probe* probe = new Probe("abc");
  {
    Holder<Probe> holder(probe);

    CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());

    CPPUNIT_ASSERT_EQUAL(probe, &holder.get());
    CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, holder.contains(*probe));
    CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));
  }
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
}

void
sk::util::test::HolderTest::
testCreateEmpty()
{
  Holder<Probe> holder;

  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));

  CPPUNIT_ASSERT_THROW(holder.get(), MissingResourceException);
  CPPUNIT_ASSERT_EQUAL(false, holder.remove());
}

void
sk::util::test::HolderTest::
testRemove()
{
  Probe* probe = new Probe("abc");
  Holder<Probe> holder(probe);

  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(true, holder.remove());
  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(false, holder.remove());
}

void
sk::util::test::HolderTest::
testRelease()
{
  Probe* probe = new Probe("abc");
  Holder<Probe> holder(probe);

  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());

  Probe* released = holder.release();

  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(probe, released);
  CPPUNIT_ASSERT_EQUAL(probe, &holder.get());

  CPPUNIT_ASSERT_THROW(holder.release(), UnsupportedOperationException);
  
  delete released;
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
}

void
sk::util::test::HolderTest::
testSet()
{
  Holder<Probe> holder(new Probe("abc"));
  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(String("abc"), holder.get().getName());

  Probe* probe = new Probe("zzz");
  CPPUNIT_ASSERT_EQUAL(2, Probe::getCounter());

  holder.set(probe);
  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(String("zzz"), holder.get().getName());

  holder.set(0);
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
}
