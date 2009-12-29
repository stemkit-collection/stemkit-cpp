/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CollectionTest.h"
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/selector/EqualValue.hxx>
#include <sk/util/assessor/EqualValues.hxx>

sk::util::test::collection::CollectionTest::
CollectionTest()
{
}

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::CollectionTest::
makeCopyingCollection()
{
  throw sk::util::UnsupportedOperationException("makeCopyingCollection()");
}

void
sk::util::test::collection::CollectionTest::
testCollectionBasics()
{
  Holder<Collection> collection(makeCopyingCollection());
  CPPUNIT_ASSERT(collection.get().isEmpty() == true);

  collection.getMutable().add("aaa");
  collection.getMutable().add("bbb");
  collection.getMutable().add("ccc");

  CPPUNIT_ASSERT(collection.get().isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.get().size());

  sk::util::Holder<sk::util::String> holder;
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::EqualValue<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::EqualValue<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::EqualValue<sk::util::String>("ccc")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::EqualValue<sk::util::String>("ddd")) == false);
}

void
sk::util::test::collection::CollectionTest::
testCollectionContains()
{
  Holder<Collection> collection(makeCopyingCollection());
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("uuu")) == false);

  collection.getMutable().add("uuu");
  collection.getMutable().add("zzz");
  collection.getMutable().add("ppp");

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("uuu")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("ppp")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("zzz")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("aaa")) == false);
}

void
sk::util::test::collection::CollectionTest::
testCollectionContainsAll()
{
  Holder<Collection> c1(makeCopyingCollection());
  Holder<Collection> c2(makeCopyingCollection());

  CPPUNIT_ASSERT(c1.get().containsAll(c2.get()) == true);

  c1.getMutable().add("aaa");
  c1.getMutable().add("bbb");
  c1.getMutable().add("ccc");

  c2.getMutable().add("ccc");
  c2.getMutable().add("bbb");
  CPPUNIT_ASSERT(c1.get().containsAll(c2.get(), sk::util::assessor::EqualValues<sk::util::String>()) == true);

  c2.getMutable().add("zzz");
  CPPUNIT_ASSERT(c1.get().containsAll(c2.get(), sk::util::assessor::EqualValues<sk::util::String>()) == false);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionClear()
{
  Holder<Collection> collection(makeCopyingCollection());

  CPPUNIT_ASSERT(collection.get().isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.get().size());

  collection.getMutable().add("aaa");
  collection.getMutable().add("bbb");
  collection.getMutable().add("ccc");
  CPPUNIT_ASSERT(collection.get().isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.get().size());

  collection.getMutable().clear();
  CPPUNIT_ASSERT(collection.get().isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.get().size());
}

void
sk::util::test::collection::CollectionTest::
testCollectionSelectorRemoveAll()
{
  Holder<Collection> collection(makeCopyingCollection());

  collection.getMutable().add("aaa");
  collection.getMutable().add("bbb");
  collection.getMutable().add("ccc");
  collection.getMutable().add("aaa");
  CPPUNIT_ASSERT_EQUAL(4, collection.get().size());

  CPPUNIT_ASSERT(collection.getMutable().removeAll(sk::util::selector::EqualValue<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT_EQUAL(2, collection.get().size());

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("aaa")) == false);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("ccc")) == true);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionCollectionRemoveAll()
{
  Holder<Collection> c1(makeCopyingCollection());
  Holder<Collection> c2(makeCopyingCollection());

  c1.getMutable().add("aaa");
  c1.getMutable().add("bbb");
  c1.getMutable().add("aaa");
  c1.getMutable().add("ccc");
  CPPUNIT_ASSERT_EQUAL(4, c1.get().size());

  c2.getMutable().add("aaa");
  c2.getMutable().add("bbb");

  CPPUNIT_ASSERT(c1.getMutable().removeAll(c2.get(), sk::util::assessor::EqualValues<sk::util::String>()) == true);
  CPPUNIT_ASSERT_EQUAL(1, c1.get().size());
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::EqualValue<sk::util::String>("ccc")) == true);
}

void
sk::util::test::collection::CollectionTest::
testCollectionSelectorRetainAll()
{
  Holder<Collection> collection(makeCopyingCollection());

  collection.getMutable().add("aaa");
  collection.getMutable().add("bbb");
  collection.getMutable().add("ccc");
  collection.getMutable().add("aaa");
  CPPUNIT_ASSERT_EQUAL(4, collection.get().size());

  CPPUNIT_ASSERT(collection.getMutable().retainAll(sk::util::selector::EqualValue<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT_EQUAL(2, collection.get().size());

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("bbb")) == false);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::EqualValue<sk::util::String>("ccc")) == false);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionCollectionRetainAll()
{
  Holder<Collection> c1(makeCopyingCollection());
  Holder<Collection> c2(makeCopyingCollection());

  c1.getMutable().add("aaa");
  c1.getMutable().add("bbb");
  c1.getMutable().add("aaa");
  c1.getMutable().add("ccc");
  CPPUNIT_ASSERT_EQUAL(4, c1.get().size());

  c2.getMutable().add("aaa");
  c2.getMutable().add("bbb");

  CPPUNIT_ASSERT(c1.getMutable().retainAll(c2.get(), sk::util::assessor::EqualValues<sk::util::String>()) == true);
  CPPUNIT_ASSERT_EQUAL(3, c1.get().size());
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::EqualValue<sk::util::String>("ccc")) == false);
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::EqualValue<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::EqualValue<sk::util::String>("aaa")) == true);
}

