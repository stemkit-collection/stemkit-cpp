/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "PrettyPrinterTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PrettyPrinterTest);

sk::util::test::PrettyPrinterTest::
PrettyPrinterTest()
{
}

sk::util::test::PrettyPrinterTest::
~PrettyPrinterTest()
{
}

void
sk::util::test::PrettyPrinterTest::
setUp()
{
}

void
sk::util::test::PrettyPrinterTest::
tearDown()
{
}

void
sk::util::test::PrettyPrinterTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
