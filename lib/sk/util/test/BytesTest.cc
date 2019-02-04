/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "BytesTest.h"
#include <sk/util/bytes.h>
#include <sk/util/inspect.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::BytesTest);

sk::util::test::BytesTest::
BytesTest()
{
}

sk::util::test::BytesTest::
~BytesTest()
{
}

void
sk::util::test::BytesTest::
setUp()
{
}

void
sk::util::test::BytesTest::
tearDown()
{
}

void
sk::util::test::BytesTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL("[ 1, 2, 3, 4 ]", sk::util::inspect(sk::util::bytes(1) << 2 << 3 << 4));
}
