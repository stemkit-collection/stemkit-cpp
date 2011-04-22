/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CompoundExceptionTest.h"
#include <sk/util/CompoundException.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/IndexOutOfBoundsException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::CompoundExceptionTest);

sk::util::test::CompoundExceptionTest::
CompoundExceptionTest()
{
}

sk::util::test::CompoundExceptionTest::
~CompoundExceptionTest()
{
}

void
sk::util::test::CompoundExceptionTest::
setUp()
{
}

void
sk::util::test::CompoundExceptionTest::
tearDown()
{
}

void
sk::util::test::CompoundExceptionTest::
test_wraps_multiple_exceptions()
{
  sk::util::ArrayList<sk::util::Exception> list;
  list.add(new sk::util::IllegalStateException("abc"));
  list.add(new sk::util::IndexOutOfBoundsException("zzz"));
  sk::util::CompoundException compound(list);

  CPPUNIT_ASSERT_EQUAL("sk::util::CompoundException", compound.getClass().getName());
  CPPUNIT_ASSERT_EQUAL("ERROR: Compound: 2: Illegal state: abc", compound.what());

  CPPUNIT_ASSERT_EQUAL(2, compound.size());
  CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: abc", compound.exceptionAt(0).what());
  CPPUNIT_ASSERT_EQUAL("ERROR: Index out of bounds: zzz", compound.exceptionAt(1).what());
}
