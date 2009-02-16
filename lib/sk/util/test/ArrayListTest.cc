/*  vim:sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ArrayListTest.h"
#include <sk/util/ArrayList.cxx>
#include "Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ArrayListTest);

sk::util::test::ArrayListTest::
ArrayListTest()
{
}

sk::util::test::ArrayListTest::
~ArrayListTest()
{
}

void
sk::util::test::ArrayListTest::
setUp()
{
  Probe::resetCounter();
}

void
sk::util::test::ArrayListTest::
tearDown()
{
  Probe::resetCounter();
}

void
sk::util::test::ArrayListTest::
testCreate()
{
  ArrayList<Probe> list;

  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_EQUAL(true, list.isEmpty());
}

void
sk::util::test::ArrayListTest::
testAdd()
{
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  ArrayList<Probe> list;
  Probe p1("aaa");
  Probe p2("bbb");
  
  list.add(p1);
  list.add(p2);
  list.add(new Probe("ccc"));

  CPPUNIT_ASSERT_EQUAL(false, list.isEmpty());
  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL(3, Probe::getCounter());

  list.clear();

  CPPUNIT_ASSERT_EQUAL(true, list.isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_EQUAL(2, Probe::getCounter());
}
