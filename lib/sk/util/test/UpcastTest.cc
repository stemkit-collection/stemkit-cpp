/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "UpcastTest.h"

#include <sk/util/Integer.h>
#include <sk/util/String.h>
#include <sk/util/upcast.cxx>
#include <sk/util/ClassCastException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::UpcastTest);

sk::util::test::UpcastTest::
UpcastTest()
{
}

sk::util::test::UpcastTest::
~UpcastTest()
{
}

void
sk::util::test::UpcastTest::
setUp()
{
}

void
sk::util::test::UpcastTest::
tearDown()
{
}

void
sk::util::test::UpcastTest::
testFailingNonConstUpcastFromObject()
{
  sk::util::Integer value(0);
  sk::util::Object& o = value;

  try {
    sk::util::upcast<sk::util::String>(o);
    CPPUNIT_FAIL("No expected exception");
  }
  catch(sk::util::ClassCastException& exception) {
    CPPUNIT_ASSERT_EQUAL("sk::util::Integer", exception.sourceName());
  }
}

void
sk::util::test::UpcastTest::
testFailingConstUpcastFromObject()
{
  try {
    sk::util::upcast<sk::util::String>(sk::util::Integer(0));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(sk::util::ClassCastException& exception) {
    CPPUNIT_ASSERT_EQUAL("sk::util::Integer", exception.sourceName());
  }
}
