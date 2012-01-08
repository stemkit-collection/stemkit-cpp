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
#include <sk/util/mapper/Inspecting.hxx>
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

  CPPUNIT_ASSERT_THROW(list.getMutable().getMutable(0), sk::util::IndexOutOfBoundsException);

  list.getMutable().add("aaa");
  list.getMutable().add("bbb");
  list.getMutable().add("ccc");

  CPPUNIT_ASSERT_EQUAL("aaa", list.getMutable().getMutable(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.getMutable().getMutable(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.getMutable().getMutable(2));

  CPPUNIT_ASSERT_THROW(list.getMutable().getMutable(3), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.getMutable().getMutable(-1), sk::util::IndexOutOfBoundsException);
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

void
sk::util::test::collection::ListTest::
testListAddFirst()
{
  sk::util::Holder<List> list(makeCopyingList());
  list.getMutable().addFirst("a");
  list.getMutable().addFirst("b");
  list.getMutable().addFirst("c");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("c", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("a", list.get().get(2));
}

void
sk::util::test::collection::ListTest::
testListAddLast()
{
  sk::util::Holder<List> list(makeCopyingList());
  list.getMutable().addLast("a");
  list.getMutable().addLast("b");
  list.getMutable().addLast("c");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());
  CPPUNIT_ASSERT_EQUAL("a", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("c", list.get().get(2));
}

void
sk::util::test::collection::ListTest::
testListGetFirstLast()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.getMutable().getFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().getLast(), sk::util::NoSuchElementException);

  list.getMutable().add("a");
  CPPUNIT_ASSERT_EQUAL("a", list.get().getFirst());
  CPPUNIT_ASSERT_EQUAL("a", list.get().getLast());

  list.getMutable().add("b");
  CPPUNIT_ASSERT_EQUAL("a", list.get().getFirst());
  CPPUNIT_ASSERT_EQUAL("b", list.get().getLast());

  list.getMutable().add("c");
  CPPUNIT_ASSERT_EQUAL("a", list.get().getFirst());
  CPPUNIT_ASSERT_EQUAL("c", list.get().getLast());
}

void
sk::util::test::collection::ListTest::
testListGetMutableFirstLast()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.getMutable().getMutableFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().getMutableLast(), sk::util::NoSuchElementException);

  list.getMutable().add("a");
  CPPUNIT_ASSERT_EQUAL("a", list.getMutable().getMutableFirst());
  CPPUNIT_ASSERT_EQUAL("a", list.getMutable().getMutableLast());

  list.getMutable().add("b");
  CPPUNIT_ASSERT_EQUAL("a", list.getMutable().getMutableFirst());
  CPPUNIT_ASSERT_EQUAL("b", list.getMutable().getMutableLast());

  list.getMutable().add("c");
  CPPUNIT_ASSERT_EQUAL("a", list.getMutable().getMutableFirst());
  CPPUNIT_ASSERT_EQUAL("c", list.getMutable().getMutableLast());
}

void
sk::util::test::collection::ListTest::
testListRemoveFirstLast()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.getMutable().removeFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().removeLast(), sk::util::NoSuchElementException);

  list.getMutable().add("a");
  list.getMutable().add("b");
  list.getMutable().add("c");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());

  list.getMutable().removeFirst();
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("c", list.get().get(1));

  list.getMutable().removeLast();
  CPPUNIT_ASSERT_EQUAL(1, list.get().size());
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(0));

  list.getMutable().removeFirst();
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());

  CPPUNIT_ASSERT_THROW(list.getMutable().removeFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().removeLast(), sk::util::NoSuchElementException);
}

void
sk::util::test::collection::ListTest::
testListCutoffFirstLast()
{
  sk::util::Holder<List> list(makeCopyingList());

  CPPUNIT_ASSERT_THROW(list.getMutable().cutoffFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().cutoffLast(), sk::util::NoSuchElementException);

  list.getMutable().add("a");
  list.getMutable().add("b");
  list.getMutable().add("c");

  CPPUNIT_ASSERT_EQUAL(3, list.get().size());

  const sk::util::String* item = list.getMutable().cutoffFirst();
  CPPUNIT_ASSERT_EQUAL(2, list.get().size());
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("c", list.get().get(1));
  CPPUNIT_ASSERT_EQUAL("a", *item);
  delete item;

  item = list.getMutable().cutoffLast();
  CPPUNIT_ASSERT_EQUAL(1, list.get().size());
  CPPUNIT_ASSERT_EQUAL("b", list.get().get(0));
  CPPUNIT_ASSERT_EQUAL("c", *item);
  delete item;

  item = list.getMutable().cutoffFirst();
  CPPUNIT_ASSERT_EQUAL(0, list.get().size());
  CPPUNIT_ASSERT_EQUAL("b", *item);
  delete item;

  CPPUNIT_ASSERT_THROW(list.getMutable().cutoffFirst(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(list.getMutable().cutoffLast(), sk::util::NoSuchElementException);
}

void
sk::util::test::collection::ListTest::
testListJoin()
{
  sk::util::Holder<List> list(makeCopyingList());
  CPPUNIT_ASSERT_EQUAL("", list.get().join(", "));

  list.getMutable().add("a");
  list.getMutable().add("b");
  list.getMutable().add("c");

  CPPUNIT_ASSERT_EQUAL("abc", list.get().join());
  CPPUNIT_ASSERT_EQUAL("a, b, c", list.get().join(", "));
  CPPUNIT_ASSERT_EQUAL("\"a\" - \"b\" - \"c\"", list.get().join(" - ", sk::util::mapper::Inspecting<sk::util::String>()));
}
