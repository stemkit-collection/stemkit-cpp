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
