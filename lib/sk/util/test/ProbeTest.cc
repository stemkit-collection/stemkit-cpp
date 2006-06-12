/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProbeTest.h"
#include "Probe.h"

sk::util::test::ProbeTest::
ProbeTest()
{
}

sk::util::test::ProbeTest::
~ProbeTest()
{
}

void
sk::util::test::ProbeTest::
setUp()
{
}

void
sk::util::test::ProbeTest::
tearDown()
{
}

void
sk::util::test::ProbeTest::
testCounter()
{
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  {
    Probe p1("aaa");
    Probe p2("bbb");
    Probe p3("ccc");

    CPPUNIT_ASSERT_EQUAL(String("aaa"), p1.getName());
    CPPUNIT_ASSERT_EQUAL(String("bbb"), p2.getName());
    CPPUNIT_ASSERT_EQUAL(String("ccc"), p3.getName());

    CPPUNIT_ASSERT_EQUAL(3, Probe::getCounter());
  }
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
}
