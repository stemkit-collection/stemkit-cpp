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
      for(int index=0; index < _content.size(); ++index) {
        processor.process(sk::util::slot::Reference<const sk::util::String>(_content[index]));
      }
    }

    void forEachSlot(const sk::util::slot::Processor<sk::util::String>& processor) {
      throw sk::util::UnsupportedOperationException("forEachSlot");
    }

    bool add(const sk::util::String& item) {
      _content.push_back(item);
      return true;
    }

    int size() const {
      return _content.size();
    }

    const sk::util::String& get(const sk::util::Selector<sk::util::String>& selector) const {
      for(int index=0; index < _content.size(); ++index) {
        if(selector.assess(_content[index]) == true) {
          return _content[index];
        }
      }
      throw sk::util::NoSuchElementException("get()");
    }

    sk::util::String& getMutable(const sk::util::Selector<sk::util::String>& selector) {
      throw sk::util::String("No getMutable() in SampleCollection");
    }

    std::vector<sk::util::String> _content;
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
      CPPUNIT_ASSERT_EQUAL("No getMutable() in SampleCollection", message);
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
