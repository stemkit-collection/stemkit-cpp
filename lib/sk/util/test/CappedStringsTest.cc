/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CappedStringsTest.h"
#include <sk/util/CappedStrings.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::CappedStringsTest);

sk::util::test::CappedStringsTest::
CappedStringsTest()
{
}

sk::util::test::CappedStringsTest::
~CappedStringsTest()
{
}

void
sk::util::test::CappedStringsTest::
setUp()
{
}

void
sk::util::test::CappedStringsTest::
tearDown()
{
}

void
sk::util::test::CappedStringsTest::
testCap()
{
  sk::util::CappedStrings data(4);
  CPPUNIT_ASSERT_EQUAL(0, data.size());
  CPPUNIT_ASSERT_EQUAL(4, data.maxItemSize());

  data << "a" << "bb";
  CPPUNIT_ASSERT_EQUAL(2, data.size());
  CPPUNIT_ASSERT_EQUAL(4, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb", data.join("-"));

  data << "cccc" << "dddddd" << "uuuuuuuuuuuuuuu";
  CPPUNIT_ASSERT_EQUAL(5, data.size());
  CPPUNIT_ASSERT_EQUAL(4, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb-cccc-dddd-uuuu", data.join("-"));

  data.set(3, "1234567");
  CPPUNIT_ASSERT_EQUAL(5, data.size());
  CPPUNIT_ASSERT_EQUAL(4, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb-cccc-1234-uuuu", data.join("-"));
}

void
sk::util::test::CappedStringsTest::
testNoCap()
{
  sk::util::CappedStrings data;
  CPPUNIT_ASSERT_EQUAL(0, data.size());
  CPPUNIT_ASSERT_EQUAL(0, data.maxItemSize());

  data << "a" << "bb";
  CPPUNIT_ASSERT_EQUAL(2, data.size());
  CPPUNIT_ASSERT_EQUAL(2, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb", data.join("-"));

  data << "cccc" << "dddddd" << "123456789";
  CPPUNIT_ASSERT_EQUAL(5, data.size());
  CPPUNIT_ASSERT_EQUAL(9, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb-cccc-dddddd-123456789", data.join("-"));

  data.set(3, "1234567");
  CPPUNIT_ASSERT_EQUAL(5, data.size());
  CPPUNIT_ASSERT_EQUAL(9, data.maxItemSize());
  CPPUNIT_ASSERT_EQUAL("a-bb-cccc-1234567-123456789", data.join("-"));
}
