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
      throw sk::util::String("No mutable forEachSlot() in the sample collection");
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

sk::util::Collection<sk::util::String>* 
sk::util::test::collection::AbstractCollectionTest::
makeCollection()
{
  return new SampleCollection();
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

