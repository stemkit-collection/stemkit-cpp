/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "LinkedListTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::LinkedListTest);

#include <sk/util/LinkedList.cxx>
#include <sk/util/String.h>

sk::util::test::collection::LinkedListTest::
LinkedListTest()
{
}

sk::util::test::collection::LinkedListTest::
~LinkedListTest()
{
}

sk::util::List<sk::util::String>*
sk::util::test::collection::LinkedListTest::
makeCopyingList()
{
  return new sk::util::LinkedList<sk::util::String>::Copying();
}

sk::util::List<sk::util::String>*
sk::util::test::collection::LinkedListTest::
makeStoringList()
{
  return new sk::util::LinkedList<sk::util::String>::Storing();
}

