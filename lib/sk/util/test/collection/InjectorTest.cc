/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "InjectorTest.h"
#include <sk/util/ArrayList.cxx>
#include <sk/util/Injector.cxx>
#include <sk/util/Reducer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::InjectorTest);

sk::util::test::collection::InjectorTest::
InjectorTest()
{
}

sk::util::test::collection::InjectorTest::
~InjectorTest()
{
}

void
sk::util::test::collection::InjectorTest::
setUp()
{
}

void
sk::util::test::collection::InjectorTest::
tearDown()
{
}

namespace {
  struct Adder : public virtual sk::util::Reducer<int> {
    int reduce(int memo, int& item) const {
      return memo + item;
    }
  };
}

void
sk::util::test::collection::InjectorTest::
testBasics()
{
  sk::util::ArrayList<int> list;
  list.add(1);
  list.add(2);
  list.add(3);

  sk::util::Injector<int> injector(list);
  CPPUNIT_ASSERT_EQUAL(6, injector.inject(Adder()));
  CPPUNIT_ASSERT_EQUAL(11, injector.inject(5, Adder()));
}
