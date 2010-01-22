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
#include <sk/util/reducer/Plus.hxx>
#include <sk/util/reducer/Multiply.hxx>
#include <sk/util/reducer/Join.hxx>

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
  struct SummingReducer : public virtual sk::util::Reducer<int> {
    int reduce(const int& memo, const int& item, const sk::util::Mapper<const int>& mapper) const {
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
  CPPUNIT_ASSERT_EQUAL(6, injector.inject(SummingReducer()));
  CPPUNIT_ASSERT_EQUAL(11, injector.inject(5, SummingReducer()));

  CPPUNIT_ASSERT_EQUAL(15, injector.inject(9, sk::util::reducer::Plus<int>()));
  CPPUNIT_ASSERT_EQUAL(12, injector.inject(2, sk::util::reducer::Multiply<int>()));

  CPPUNIT_ASSERT_EQUAL(15, injector.inject(9, sk::util::reducer::Join<int>()));
  CPPUNIT_ASSERT_EQUAL(14, injector.inject(sk::util::reducer::Join<int>(4))); // 1 + (4) + 2 + (4) + 3
  CPPUNIT_ASSERT_EQUAL(27, injector.inject(9, sk::util::reducer::Join<int>(4))); // 9 + (4) + 1 + (4) + 2 + (4) + 3
}

void
sk::util::test::collection::InjectorTest::
testJoinStrings()
{
  sk::util::ArrayList<sk::util::String>::Copying list;
  list.add("aaa");
  list.add("bbb");
  list.add("ccc");

  sk::util::Injector<sk::util::String> injector(list);
  CPPUNIT_ASSERT_EQUAL("aaa, bbb, ccc", injector.inject(sk::util::reducer::Join<sk::util::String>(", ")));
}
