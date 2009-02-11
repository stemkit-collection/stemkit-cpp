/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ClassTest.h"
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ClassTest);

sk::util::test::ClassTest::
ClassTest()
{
}

sk::util::test::ClassTest::
~ClassTest()
{
}

void
sk::util::test::ClassTest::
setUp()
{
}

void
sk::util::test::ClassTest::
tearDown()
{
}

void
sk::util::test::ClassTest::
testBasics()
{
  Class klass("abcdef");

  CPPUNIT_ASSERT_EQUAL(String("abcdef"), klass.getName());
  CPPUNIT_ASSERT_EQUAL(String("sk::util::Class"), klass.getClass().getName());
}

namespace {
  struct Class : public sk::util::Class {
    Class() 
      : sk::util::Class("abc") {}

    uint64_t getId() const {
      return 21;
    }
  } klass;
}

void
sk::util::test::ClassTest::
testToString()
{
  CPPUNIT_ASSERT_EQUAL(String("sk::util::Class<abc>#21"), klass.toString());
}
