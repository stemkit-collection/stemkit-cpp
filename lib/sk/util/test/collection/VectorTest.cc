/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "VectorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::collection::VectorTest);

#include <sk/util/Vector.cxx>
#include <sk/util/String.h>

sk::util::test::collection::VectorTest::
VectorTest()
{
}

sk::util::test::collection::VectorTest::
~VectorTest()
{
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::VectorTest::
makeCopyingList()
{
  return new sk::util::Vector<sk::util::String>::Copying();
}

sk::util::List<sk::util::String>* 
sk::util::test::collection::VectorTest::
makeStoringList()
{
  return new sk::util::Vector<sk::util::String>::Storing();
}

void
sk::util::test::collection::VectorTest::
setUp()
{
}

void
sk::util::test::collection::VectorTest::
tearDown()
{
}
