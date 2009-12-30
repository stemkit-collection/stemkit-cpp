/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ArrayListTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::ArrayListTest);

#include <sk/util/ArrayList.cxx>
#include <sk/util/String.h>

sk::util::test::collection::ArrayListTest::
ArrayListTest()
{
}

sk::util::test::collection::ArrayListTest::
~ArrayListTest()
{
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::ArrayListTest::
makeCopyingList()
{
  return new sk::util::ArrayList<sk::util::String>::Copying();
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::ArrayListTest::
makeStoringList()
{
  return new sk::util::ArrayList<sk::util::String>::Storing();
}

