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
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::AbstractListTest);

namespace {
  struct SampleList : public sk::util::AbstractList<sk::util::String> {
    void forEachSlot(const sk::util::slot::Processor<const sk::util::String>& processor) const {
      throw sk::util::UnsupportedOperationException("forEachSlot()");
    }

    void forEachSlot(const sk::util::slot::Processor<sk::util::String>& processor) {
      throw sk::util::UnsupportedOperationException("forEachSlot()");
    }
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
testBasics()
{
  SampleList list;
}
