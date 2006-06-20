/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ArrayListTest.h"
#include <sk/util/ArrayList.h>
#include "Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ArrayListTest);

sk::util::test::ArrayListTest::
ArrayListTest()
{
}

sk::util::test::ArrayListTest::
~ArrayListTest()
{
}

void
sk::util::test::ArrayListTest::
setUp()
{
}

void
sk::util::test::ArrayListTest::
tearDown()
{
}

void
sk::util::test::ArrayListTest::
testCreate()
{
  ArrayList<Probe> list;
}
