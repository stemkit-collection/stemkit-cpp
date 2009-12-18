/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ListTest.h"
#include <sk/util/AbstractList.cxx>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/stl/VectorPopulator.cxx>
#include <sk/util/selector/Equal.cxx>
#include <sk/util/String.h>
#include <list>

sk::util::test::collection::ListTest::
ListTest()
{
}

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::ListTest::
makeCollection()
{
  return makeList();
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::ListTest::
makeList()
{
  throw sk::util::UnsupportedOperationException("makeList()");
}

void 
sk::util::test::collection::ListTest::
testListAdd()
{
  sk::util::Holder<List> list(makeList());

  CPPUNIT_ASSERT_EQUAL(0, list.get().size());

  list.get().add("aaa");
  list.get().add("bbb");
  list.get().add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());

  std::vector<sk::util::String> depot;
  list.get().forEach(sk::util::stl::VectorPopulator<sk::util::String>(depot));

  CPPUNIT_ASSERT_EQUAL("aaa", depot.at(0));
  CPPUNIT_ASSERT_EQUAL("bbb", depot.at(1));
  CPPUNIT_ASSERT_EQUAL("ccc", depot.at(2));
}

void 
sk::util::test::collection::ListTest::
testListGet()
{
  sk::util::Holder<List> list(makeList());

  CPPUNIT_ASSERT_THROW(list.get().get(0), sk::util::IndexOutOfBoundsException);

  list.get().add("aaa");
  list.get().add("bbb");
  list.get().add("ccc");

  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(2));

  CPPUNIT_ASSERT_THROW(list.get().get(3), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.get().get(-1), sk::util::IndexOutOfBoundsException);
}

void 
sk::util::test::collection::ListTest::
testListGetMutable()
{
  sk::util::Holder<List> list(makeList());

  CPPUNIT_ASSERT_THROW(list.get().get(0), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.get().get(-1), sk::util::IndexOutOfBoundsException);

  list.get().add("aaa");

  try {
    list.get().getMutable(0);
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::String& message) {
    CPPUNIT_ASSERT_EQUAL("No mutable forEachSlot() in the sample collection", message);
  }
}

void 
sk::util::test::collection::ListTest::
testListIndexOf()
{
  sk::util::Holder<List> list(makeList());

  CPPUNIT_ASSERT_EQUAL(-1, list.get().indexOf("aaa"));
  CPPUNIT_ASSERT_EQUAL(-1, list.get().lastIndexOf("zzz"));

  list.get().add("aaa");
  list.get().add("bbb");
  list.get().add("aaa");
  list.get().add("zzz");

  CPPUNIT_ASSERT_EQUAL(0, list.get().indexOf(sk::util::selector::Equal<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.get().indexOf(sk::util::selector::Equal<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.get().indexOf(sk::util::selector::Equal<sk::util::String>("zzz")));

  CPPUNIT_ASSERT_EQUAL(2, list.get().lastIndexOf(sk::util::selector::Equal<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.get().lastIndexOf(sk::util::selector::Equal<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.get().lastIndexOf(sk::util::selector::Equal<sk::util::String>("zzz")));
}

void 
sk::util::test::collection::ListTest::
testListRemove()
{
  sk::util::Holder<List> list(makeList());
  CPPUNIT_ASSERT_THROW(list.get().remove(0), sk::util::IndexOutOfBoundsException);

  list.get().add("aaa");
  list.get().add("bbb");
  list.get().add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());

  list.get().remove(1);
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(1));

  list.get().remove(0);
  CPPUNIT_ASSERT_EQUAL(1, list.get().size());
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(0));

  list.get().remove(0);
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_THROW(list.get().remove(0), sk::util::IndexOutOfBoundsException);
}

void 
sk::util::test::collection::ListTest::
testListSet()
{
  sk::util::Holder<List> list(makeList());

  CPPUNIT_ASSERT_THROW(list.get().set(0, "abc"), sk::util::IndexOutOfBoundsException);
  list.get().add("aaa");
  list.get().add("bbb");
  list.get().add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(2));

  list.get().set(2, "CCC");
  list.get().set(0, "AAA");
  list.get().set(1, "BBB");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("AAA", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("BBB", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("CCC", list.get().get(2));

  CPPUNIT_ASSERT_THROW(list.get().set(3, "abc"), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::collection::ListTest::
testListInspect()
{
  sk::util::Holder<List> list(makeList());
  CPPUNIT_ASSERT_EQUAL("[]", list.get().inspect());

  list.get().add("a");
  list.get().add("b");
  list.get().add("c");

  CPPUNIT_ASSERT_EQUAL("[3: 0&\"a\", 1&\"b\", 2&\"c\" ]", list.get().inspect());
}
