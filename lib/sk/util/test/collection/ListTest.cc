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
#include <sk/util/ImmutableObjectException.h>
#include <sk/util/stl/VectorPopulator.hxx>
#include <sk/util/selector/EqualValue.hxx>
#include <sk/util/String.h>
#include <list>

sk::util::test::collection::ListTest::
ListTest()
{
}

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::ListTest::
makeCopyingCollection()
{
  return makeCopyingList();
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::ListTest::
makeCopyingList()
{
  throw sk::util::UnsupportedOperationException("makeCopyingList()");
}

void 
sk::util::test::collection::ListTest::
testListAdd()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_EQUAL(0, list.get().size());

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");

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
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.get().get(0), sk::util::IndexOutOfBoundsException);

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");

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
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.get().get(0), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.get().get(-1), sk::util::IndexOutOfBoundsException);

  list.getMutable().add("aaa");

  try {
    list.getMutable().getMutable(0);
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::ImmutableObjectException& exception) {}
}

void 
sk::util::test::collection::ListTest::
testListIndexOf()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_EQUAL(-1, list.get().indexOf("aaa"));
  CPPUNIT_ASSERT_EQUAL(-1, list.get().lastIndexOf("zzz"));

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("aaa");
  list.getMutable().add("zzz");

  CPPUNIT_ASSERT_EQUAL(0, list.get().indexOf(sk::util::selector::EqualValue<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.get().indexOf(sk::util::selector::EqualValue<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.get().indexOf(sk::util::selector::EqualValue<sk::util::String>("zzz")));

  CPPUNIT_ASSERT_EQUAL(2, list.get().lastIndexOf(sk::util::selector::EqualValue<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.get().lastIndexOf(sk::util::selector::EqualValue<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.get().lastIndexOf(sk::util::selector::EqualValue<sk::util::String>("zzz")));
}

void 
sk::util::test::collection::ListTest::
testListRemove()
{
  sk::util::Holder<List> list(makeCopyingList());
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(0), sk::util::IndexOutOfBoundsException);

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());

  list.getMutable().remove(1);
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(1));

  list.getMutable().remove(0);
  CPPUNIT_ASSERT_EQUAL(1, list.get().size());
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(0));

  list.getMutable().remove(0);
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_THROW(list.getMutable().remove(0), sk::util::IndexOutOfBoundsException);
}

void 
sk::util::test::collection::ListTest::
testListSet()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.getMutable().set(0, "abc"), sk::util::IndexOutOfBoundsException);
  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get().get(2));

  list.getMutable().set(2, "CCC");
  list.getMutable().set(0, "AAA");
  list.getMutable().set(1, "BBB");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("AAA", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("BBB", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("CCC", list.get().get(2));

  CPPUNIT_ASSERT_THROW(list.getMutable().set(3, "abc"), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::collection::ListTest::
testListInspect()
{
  sk::util::Holder<List> list(makeCopyingList());
  CPPUNIT_ASSERT_EQUAL("[]", list.get().inspect());

  list.getMutable().add("a");
  list.getMutable().add("b");
  list.getMutable().add("c");

  CPPUNIT_ASSERT_EQUAL("[3: 0&\"a\", 1&\"b\", 2&\"c\" ]", list.get().inspect());
}
