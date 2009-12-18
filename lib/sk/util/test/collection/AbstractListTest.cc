/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "AbstractListTest.h"
#include <sk/util/AbstractList.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/stl/VectorPopulator.cxx>
#include <sk/util/selector/Equal.cxx>
#include <sk/util/String.h>
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::AbstractListTest);

namespace {
  struct SampleList : public sk::util::AbstractList<sk::util::String> {
    void forEachSlot(const sk::util::slot::Processor<const sk::util::String>& processor) const {
      for(container::const_iterator iterator = _content.begin(); iterator != _content.end(); ++iterator) {
        processor.process(sk::util::slot::Reference<const sk::util::String>(*iterator));
      }
    }

    void forEachSlot(const sk::util::slot::Processor<sk::util::String>& processor) {
      throw sk::util::String("No mutable forEachSlot() in the sample collection");
    }

    void add(int index, const sk::util::String& item) {
      if((index < 0) && (index > size())) {
        throw sk::util::IndexOutOfBoundsException("add");
      }
      
      container::iterator iterator = _content.begin();
      while(index--) {
        ++iterator;
      }
      _content.insert(iterator, item);
    }
    using sk::util::AbstractList<sk::util::String>::add;

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
    using sk::util::AbstractList<sk::util::String>::remove;

    typedef std::list<sk::util::String> container;
    container _content;
  };
}

sk::util::test::collection::AbstractListTest::
AbstractListTest()
{
}

sk::util::test::collection::AbstractListTest::
~AbstractListTest()
{
}

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::AbstractListTest::
makeCollection()
{
  return new SampleList();
}

void
sk::util::test::collection::AbstractListTest::
setUp()
{
}

void
sk::util::test::collection::AbstractListTest::
tearDown()
{
}

void 
sk::util::test::collection::AbstractListTest::
testListAdd()
{
  SampleList list;

  CPPUNIT_ASSERT_EQUAL(0, list.size());

  list.add("aaa");
  list.add("bbb");
  list.add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.size());

  std::vector<sk::util::String> depot;
  list.forEach(sk::util::stl::VectorPopulator<sk::util::String>(depot));

  CPPUNIT_ASSERT_EQUAL("aaa", depot.at(0));
  CPPUNIT_ASSERT_EQUAL("bbb", depot.at(1));
  CPPUNIT_ASSERT_EQUAL("ccc", depot.at(2));
}

void 
sk::util::test::collection::AbstractListTest::
testListGet()
{
  SampleList list;

  CPPUNIT_ASSERT_THROW(list.get(0), sk::util::IndexOutOfBoundsException);

  list.add("aaa");
  list.add("bbb");
  list.add("ccc");

  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(2));

  CPPUNIT_ASSERT_THROW(list.get(3), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.get(-1), sk::util::IndexOutOfBoundsException);
}

void 
sk::util::test::collection::AbstractListTest::
testListGetMutable()
{
  SampleList list;

  CPPUNIT_ASSERT_THROW(list.get(0), sk::util::IndexOutOfBoundsException);
  CPPUNIT_ASSERT_THROW(list.get(-1), sk::util::IndexOutOfBoundsException);

  list.add("aaa");

  try {
    list.getMutable(0);
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::String& message) {
    CPPUNIT_ASSERT_EQUAL("No mutable forEachSlot() in the sample collection", message);
  }
}

void 
sk::util::test::collection::AbstractListTest::
testListIndexOf()
{
  SampleList list;

  CPPUNIT_ASSERT_EQUAL(-1, list.indexOf("aaa"));
  CPPUNIT_ASSERT_EQUAL(-1, list.lastIndexOf("zzz"));

  list.add("aaa");
  list.add("bbb");
  list.add("aaa");
  list.add("zzz");

  CPPUNIT_ASSERT_EQUAL(0, list.indexOf(sk::util::selector::Equal<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.indexOf(sk::util::selector::Equal<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.indexOf(sk::util::selector::Equal<sk::util::String>("zzz")));

  CPPUNIT_ASSERT_EQUAL(2, list.lastIndexOf(sk::util::selector::Equal<sk::util::String>("aaa")));
  CPPUNIT_ASSERT_EQUAL(1, list.lastIndexOf(sk::util::selector::Equal<sk::util::String>("bbb")));
  CPPUNIT_ASSERT_EQUAL(3, list.lastIndexOf(sk::util::selector::Equal<sk::util::String>("zzz")));
}

void 
sk::util::test::collection::AbstractListTest::
testListRemove()
{
  SampleList list;
  CPPUNIT_ASSERT_THROW(list.remove(0), sk::util::IndexOutOfBoundsException);

  list.add("aaa");
  list.add("bbb");
  list.add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.size());

  list.remove(1);
  CPPUNIT_ASSERT_EQUAL(2, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(1));

  list.remove(0);
  CPPUNIT_ASSERT_EQUAL(1, list.size());
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(0));

  list.remove(0);
  CPPUNIT_ASSERT_EQUAL(0, list.size());
  CPPUNIT_ASSERT_THROW(list.remove(0), sk::util::IndexOutOfBoundsException);
}

void 
sk::util::test::collection::AbstractListTest::
testListSet()
{
  SampleList list;

  CPPUNIT_ASSERT_THROW(list.set(0, "abc"), sk::util::IndexOutOfBoundsException);
  list.add("aaa");
  list.add("bbb");
  list.add("ccc");

  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL("aaa", list.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", list.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", list.get(2));

  list.set(2, "CCC");
  list.set(0, "AAA");
  list.set(1, "BBB");

  CPPUNIT_ASSERT_EQUAL(3, list.size());
  CPPUNIT_ASSERT_EQUAL("AAA", list.get(0));
  CPPUNIT_ASSERT_EQUAL("BBB", list.get(1));
  CPPUNIT_ASSERT_EQUAL("CCC", list.get(2));

  CPPUNIT_ASSERT_THROW(list.set(3, "abc"), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::collection::AbstractListTest::
testListInspect()
{
  SampleList list;
  CPPUNIT_ASSERT_EQUAL("[]", list.inspect());

  list.add("a");
  list.add("b");
  list.add("c");

  CPPUNIT_ASSERT_EQUAL("[3: 0&\"a\", 1&\"b\", 2&\"c\" ]", list.inspect());
}
