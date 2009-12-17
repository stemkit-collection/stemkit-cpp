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
#include <sk/util/selector/Equal.cxx>
#include <sk/util/assessor/EqualObjects.cxx>

sk::util::test::collection::CollectionTest::
CollectionTest()
{
}

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::CollectionTest::
makeCollection()
{
  throw sk::util::UnsupportedOperationException("makeCollection()");
}

void
sk::util::test::collection::CollectionTest::
testCollectionBasics()
{
  Holder<Collection> collection(makeCollection());
  CPPUNIT_ASSERT(collection.get().isEmpty() == true);

  collection.get().add("aaa");
  collection.get().add("bbb");
  collection.get().add("ccc");

  CPPUNIT_ASSERT(collection.get().isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.get().size());

  sk::util::Holder<const sk::util::String> holder;
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::Equal<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::Equal<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::Equal<sk::util::String>("ccc")) == true);
  CPPUNIT_ASSERT(collection.get().find(holder, sk::util::selector::Equal<sk::util::String>("ddd")) == false);

  sk::util::Holder<sk::util::String> mutableHolder;

  try {
    collection.get().find(mutableHolder, sk::util::selector::Equal<sk::util::String>("aaa"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::String& message) {
    CPPUNIT_ASSERT_EQUAL("No mutable forEachSlot() in the sample collection", message);
  }
}

void
sk::util::test::collection::CollectionTest::
testCollectionContains()
{
  Holder<Collection> collection(makeCollection());
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("uuu")) == false);

  collection.get().add("uuu");
  collection.get().add("zzz");
  collection.get().add("ppp");

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("uuu")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("ppp")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("zzz")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("aaa")) == false);
}

void
sk::util::test::collection::CollectionTest::
testCollectionContainsAll()
{
  Holder<Collection> c1(makeCollection());
  Holder<Collection> c2(makeCollection());

  CPPUNIT_ASSERT(c1.get().containsAll(c2.get()) == true);

  c1.get().add("aaa");
  c1.get().add("bbb");
  c1.get().add("ccc");

  c2.get().add("ccc");
  c2.get().add("bbb");
  CPPUNIT_ASSERT(c1.get().containsAll(c2.get(), sk::util::assessor::EqualObjects<sk::util::String>()) == true);

  c2.get().add("zzz");
  CPPUNIT_ASSERT(c1.get().containsAll(c2.get(), sk::util::assessor::EqualObjects<sk::util::String>()) == false);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionClear()
{
  Holder<Collection> collection(makeCollection());

  CPPUNIT_ASSERT(collection.get().isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.get().size());

  collection.get().add("aaa");
  collection.get().add("bbb");
  collection.get().add("ccc");
  CPPUNIT_ASSERT(collection.get().isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.get().size());

  collection.get().clear();
  CPPUNIT_ASSERT(collection.get().isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.get().size());
}

void
sk::util::test::collection::CollectionTest::
testCollectionSelectorRemoveAll()
{
  Holder<Collection> collection(makeCollection());

  collection.get().add("aaa");
  collection.get().add("bbb");
  collection.get().add("ccc");
  collection.get().add("aaa");
  CPPUNIT_ASSERT_EQUAL(4, collection.get().size());

  CPPUNIT_ASSERT(collection.get().removeAll(sk::util::selector::Equal<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT_EQUAL(2, collection.get().size());

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("aaa")) == false);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("ccc")) == true);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionCollectionRemoveAll()
{
  Holder<Collection> c1(makeCollection());
  Holder<Collection> c2(makeCollection());

  c1.get().add("aaa");
  c1.get().add("bbb");
  c1.get().add("aaa");
  c1.get().add("ccc");
  CPPUNIT_ASSERT_EQUAL(4, c1.get().size());

  c2.get().add("aaa");
  c2.get().add("bbb");

  CPPUNIT_ASSERT(c1.get().removeAll(c2.get(), sk::util::assessor::EqualObjects<sk::util::String>()) == true);
  CPPUNIT_ASSERT_EQUAL(1, c1.get().size());
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::Equal<sk::util::String>("ccc")) == true);
}

void
sk::util::test::collection::CollectionTest::
testCollectionSelectorRetainAll()
{
  Holder<Collection> collection(makeCollection());

  collection.get().add("aaa");
  collection.get().add("bbb");
  collection.get().add("ccc");
  collection.get().add("aaa");
  CPPUNIT_ASSERT_EQUAL(4, collection.get().size());

  CPPUNIT_ASSERT(collection.get().retainAll(sk::util::selector::Equal<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT_EQUAL(2, collection.get().size());

  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("bbb")) == false);
  CPPUNIT_ASSERT(collection.get().contains(sk::util::selector::Equal<sk::util::String>("ccc")) == false);
}

void 
sk::util::test::collection::CollectionTest::
testCollectionCollectionRetainAll()
{
  Holder<Collection> c1(makeCollection());
  Holder<Collection> c2(makeCollection());

  c1.get().add("aaa");
  c1.get().add("bbb");
  c1.get().add("aaa");
  c1.get().add("ccc");
  CPPUNIT_ASSERT_EQUAL(4, c1.get().size());

  c2.get().add("aaa");
  c2.get().add("bbb");

  CPPUNIT_ASSERT(c1.get().retainAll(c2.get(), sk::util::assessor::EqualObjects<sk::util::String>()) == true);
  CPPUNIT_ASSERT_EQUAL(3, c1.get().size());
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::Equal<sk::util::String>("ccc")) == false);
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::Equal<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(c1.get().contains(sk::util::selector::Equal<sk::util::String>("aaa")) == true);
}

