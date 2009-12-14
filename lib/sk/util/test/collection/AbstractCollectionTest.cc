/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "AbstractCollectionTest.h"
#include <sk/util/AbstractCollection.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/String.h>
#include <sk/util/selector/Equal.cxx>
#include <sk/util/assessor/EqualObjects.cxx>
#include <sk/util/slot/Reference.cxx>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::AbstractCollectionTest);

namespace {
  struct SampleCollection : public virtual sk::util::AbstractCollection<sk::util::String> {
    void forEachSlot(const sk::util::slot::Processor<const sk::util::String>& processor) const {
      for(container::const_iterator iterator = _content.begin(); iterator != _content.end(); ++iterator) {
        processor.process(sk::util::slot::Reference<const sk::util::String>(*iterator));
      }
    }

    void forEachSlot(const sk::util::slot::Processor<sk::util::String>& processor) {
      throw sk::util::String("No mutable forEachSlot() in SampleCollection");
    }

    bool add(const sk::util::String& item) {
      _content.push_back(item);
      return true;
    }

    int size() const {
      return _content.size();
    }

    bool remove(const sk::util::Selector<sk::util::String>& selector) {
      for(container::iterator iterator = _content.begin(); iterator != _content.end(); ++iterator) {
        if(selector.assess(*iterator) == true) {
          _content.erase(iterator);
          return true;
        }
      }
      return false;
    }

    typedef std::vector<sk::util::String> container;
    container _content;
  };
}

sk::util::test::collection::AbstractCollectionTest::
AbstractCollectionTest()
{
}

sk::util::test::collection::AbstractCollectionTest::
~AbstractCollectionTest()
{
}

void
sk::util::test::collection::AbstractCollectionTest::
setUp()
{
}

void
sk::util::test::collection::AbstractCollectionTest::
tearDown()
{
}

void
sk::util::test::collection::AbstractCollectionTest::
testBasics()
{
  SampleCollection collection;
  CPPUNIT_ASSERT(collection.isEmpty() == true);

  collection.add("aaa");
  collection.add("bbb");
  collection.add("ccc");

  CPPUNIT_ASSERT(collection.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.size());

  sk::util::Holder<const sk::util::String> holder;
  CPPUNIT_ASSERT(collection.find(holder, sk::util::selector::Equal<sk::util::String>("aaa")) == true);
  CPPUNIT_ASSERT(collection.find(holder, sk::util::selector::Equal<sk::util::String>("bbb")) == true);
  CPPUNIT_ASSERT(collection.find(holder, sk::util::selector::Equal<sk::util::String>("ccc")) == true);
  CPPUNIT_ASSERT(collection.find(holder, sk::util::selector::Equal<sk::util::String>("ddd")) == false);

  sk::util::Holder<sk::util::String> mutableHolder;

  try {
    collection.find(mutableHolder, sk::util::selector::Equal<sk::util::String>("aaa"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::String& message) {
    CPPUNIT_ASSERT_EQUAL("No mutable forEachSlot() in SampleCollection", message);
  }
}

void
sk::util::test::collection::AbstractCollectionTest::
testContains()
{
  SampleCollection collection;
  CPPUNIT_ASSERT(collection.contains(sk::util::selector::Equal<sk::util::String>("uuu")) == false);

  collection.add("uuu");
  collection.add("zzz");
  collection.add("ppp");

  CPPUNIT_ASSERT(collection.contains(sk::util::selector::Equal<sk::util::String>("uuu")) == true);
  CPPUNIT_ASSERT(collection.contains(sk::util::selector::Equal<sk::util::String>("ppp")) == true);
  CPPUNIT_ASSERT(collection.contains(sk::util::selector::Equal<sk::util::String>("zzz")) == true);
  CPPUNIT_ASSERT(collection.contains(sk::util::selector::Equal<sk::util::String>("aaa")) == false);
}

void
sk::util::test::collection::AbstractCollectionTest::
testContainsAll()
{
  SampleCollection c1;
  SampleCollection c2;

  CPPUNIT_ASSERT(c1.containsAll(c2) == true);

  c1.add("aaa");
  c1.add("bbb");
  c1.add("ccc");

  c2.add("ccc");
  c2.add("bbb");
  CPPUNIT_ASSERT(c1.containsAll(c2, sk::util::assessor::EqualObjects<sk::util::String>()) == true);

  c2.add("zzz");
  CPPUNIT_ASSERT(c1.containsAll(c2, sk::util::assessor::EqualObjects<sk::util::String>()) == false);
}

void 
sk::util::test::collection::AbstractCollectionTest::
testClear()
{
  SampleCollection collection;

  CPPUNIT_ASSERT(collection.isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.size());

  collection.add("aaa");
  collection.add("bbb");
  collection.add("ccc");
  CPPUNIT_ASSERT(collection.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, collection.size());

  collection.clear();
  CPPUNIT_ASSERT(collection.isEmpty() == true);
  CPPUNIT_ASSERT_EQUAL(0, collection.size());
}
