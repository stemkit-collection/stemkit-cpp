/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProbeTest.h"
#include <sk/util/test/Probe.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ProbeTest);

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
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
  {
    test::Probe<String> p1("aaa");
    test::Probe<String> p2("bbb");
    test::Probe<String> p3("ccc");

    CPPUNIT_ASSERT_EQUAL(String("aaa"), p1);
    CPPUNIT_ASSERT_EQUAL(String("bbb"), p2);
    CPPUNIT_ASSERT_EQUAL(String("ccc"), p3);

    CPPUNIT_ASSERT_EQUAL(3, test::Probe<String>::getCounter());
  }
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
}
