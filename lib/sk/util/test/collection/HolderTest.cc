/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "HolderTest.h"
#include <sk/util/Holder.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/test/Probe.hxx>

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
  test::Probe<String>::resetCounter();
}

void
sk::util::test::HolderTest::
tearDown()
{
  test::Probe<String>::resetCounter();
}

void
sk::util::test::HolderTest::
testCreateWithReference()
{
  test::Probe<String> probe("abc");
  Holder<test::Probe<String> > holder(probe);

  CPPUNIT_ASSERT_EQUAL(&probe, &holder.getMutable());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.contains(probe));
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(test::Probe<String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(false, holder.isOwner());
}

void
sk::util::test::HolderTest::
testCreateWithPointer()
{
  test::Probe<String>* probe = new test::Probe<String>("abc");
  {
    Holder<test::Probe<String> > holder(probe);

    CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());

    CPPUNIT_ASSERT_EQUAL(probe, &holder.getMutable());
    CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, holder.contains(*probe));
    CPPUNIT_ASSERT_EQUAL(false, holder.contains(test::Probe<String>("bbb")));
    CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  }
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
}

void
sk::util::test::HolderTest::
testCreateEmpty()
{
  Holder<test::Probe<String> > holder;

  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(test::Probe<String>("bbb")));

  CPPUNIT_ASSERT_THROW(holder.get(), MissingResourceException);
  CPPUNIT_ASSERT_EQUAL(false, holder.remove());
}

void
sk::util::test::HolderTest::
testRemove()
{
  test::Probe<String>* probe = new test::Probe<String>("abc");
  Holder<test::Probe<String> > holder(probe);

  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL(true, holder.remove());
  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL(false, holder.remove());
}

void
sk::util::test::HolderTest::
testRelease()
{
  test::Probe<String>* probe = new test::Probe<String>("abc");
  Holder<test::Probe<String> > holder(probe);

  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());

  test::Probe<String>* released = holder.release();

  CPPUNIT_ASSERT_EQUAL(false, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(probe, released);
  CPPUNIT_ASSERT_EQUAL(probe, &holder.getMutable());

  CPPUNIT_ASSERT_THROW(holder.release(), UnsupportedOperationException);
  
  delete released;
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
}

void
sk::util::test::HolderTest::
testSet()
{
  Holder<test::Probe<String> > holder(new test::Probe<String>("abc"));
  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL("abc", holder.get());

  test::Probe<String>* probe = new test::Probe<String>("zzz");
  CPPUNIT_ASSERT_EQUAL(2, test::Probe<String>::getCounter());

  holder.set(probe);
  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL("zzz", holder.get());

  holder.set(0);
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
}

void
sk::util::test::HolderTest::
testInspect()
{
  sk::util::String s("abcd");
  sk::util::Holder<sk::util::String> holder;
  CPPUNIT_ASSERT_EQUAL("()", holder.inspect());

  holder.set(s);
  CPPUNIT_ASSERT_EQUAL("(&\"abcd\")", holder.inspect());

  holder.set(new sk::util::String("zzz"));
  CPPUNIT_ASSERT_EQUAL("(*\"zzz\")", holder.inspect());

  delete holder.deprive();
  CPPUNIT_ASSERT_EQUAL("(*<null>)", holder.inspect());
}
