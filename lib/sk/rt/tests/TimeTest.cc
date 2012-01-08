/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "TimeTest.h"
#include <sk/rt/Time.h>
#include <sk/util/ArrayList.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::TimeTest);

sk::rt::tests::TimeTest::
TimeTest()
{
}

sk::rt::tests::TimeTest::
~TimeTest()
{
}

void
sk::rt::tests::TimeTest::
setUp()
{
}

void
sk::rt::tests::TimeTest::
tearDown()
{
}

void
sk::rt::tests::TimeTest::
testBasics()
{
  sk::rt::Time t = sk::rt::Time::at(127);
  CPPUNIT_ASSERT_EQUAL(time_t(127), t.getSeconds());
  CPPUNIT_ASSERT_EQUAL(uint32_t(0), t.getMicroseconds());

  CPPUNIT_ASSERT_EQUAL("<Time: date=69/12/31, time=16:02:07.0>", t.inspect());
  CPPUNIT_ASSERT_EQUAL("<Time: date=69/12/31, time=16:02:07.478>", sk::rt::Time::at(127, 478).inspect());
}

void
sk::rt::tests::TimeTest::
testOrdering()
{
  sk::rt::Time t1 = sk::rt::Time::at(10);
  sk::rt::Time t2 = sk::rt::Time::at(10);
  sk::rt::Time t3 = sk::rt::Time::at(9);
  sk::rt::Time t4 = sk::rt::Time::at(5, 127);
  sk::rt::Time t5 = sk::rt::Time::at(15, 4);

  CPPUNIT_ASSERT(t1 == t2);
  CPPUNIT_ASSERT(t1 <= t2);
  CPPUNIT_ASSERT(t1 >= t2);

  CPPUNIT_ASSERT(t3 < t2);
  CPPUNIT_ASSERT(t3 <= t2);

  CPPUNIT_ASSERT(t3 < t5);
  CPPUNIT_ASSERT(t3 <= t5);

  CPPUNIT_ASSERT(t4 < t3);
  CPPUNIT_ASSERT(t4 <= t3);

  CPPUNIT_ASSERT(t3 > t4);
  CPPUNIT_ASSERT(t3 >= t4);

  CPPUNIT_ASSERT(t5 > t4);
  CPPUNIT_ASSERT(t5 >= t4);
}

void
sk::rt::tests::TimeTest::
testSort()
{
  sk::util::ArrayList<sk::rt::Time> list;
  list.add(new sk::rt::Time(sk::rt::Time::at(15)));
  list.add(new sk::rt::Time(sk::rt::Time::at(14)));
  list.add(new sk::rt::Time(sk::rt::Time::at(10)));
  list.add(new sk::rt::Time(sk::rt::Time::at(17)));

  list.sort();

  CPPUNIT_ASSERT_EQUAL(time_t(10), list.get(0).getSeconds());
  CPPUNIT_ASSERT_EQUAL(time_t(14), list.get(1).getSeconds());
  CPPUNIT_ASSERT_EQUAL(time_t(15), list.get(2).getSeconds());
  CPPUNIT_ASSERT_EQUAL(time_t(17), list.get(3).getSeconds());
}
