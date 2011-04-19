/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ExceptionProxyTest.h"
#include <sk/util/ExceptionProxy.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/Strings.h>
#include <stdexcept>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ExceptionProxyTest);

sk::util::test::ExceptionProxyTest::
ExceptionProxyTest()
{
}

sk::util::test::ExceptionProxyTest::
~ExceptionProxyTest()
{
}

void
sk::util::test::ExceptionProxyTest::
setUp()
{
}

void
sk::util::test::ExceptionProxyTest::
tearDown()
{
}

void
sk::util::test::ExceptionProxyTest::
test_wraps_stemkit_exception()
{
  sk::util::Exception original("abc");
  sk::util::ExceptionProxy proxy("zzz", original);

  CPPUNIT_ASSERT_EQUAL("sk::util::Exception#zzz", proxy.getClass().getName());
  CPPUNIT_ASSERT_EQUAL("ERROR: zzz: abc", proxy.what());
}

void
sk::util::test::ExceptionProxyTest::
test_wraps_stemkit_derived_exception()
{
  sk::util::IllegalStateException original("abc");
  sk::util::ExceptionProxy proxy("zzz", original);

  CPPUNIT_ASSERT_EQUAL("sk::util::IllegalStateException#zzz", proxy.getClass().getName());
  CPPUNIT_ASSERT_EQUAL("ERROR: zzz: Illegal state: abc", proxy.what());
}

void
sk::util::test::ExceptionProxyTest::
test_wraps_std_exception()
{
  std::out_of_range original("abc");
  sk::util::ExceptionProxy proxy("zzz", original);

  CPPUNIT_ASSERT_EQUAL("std::exception#zzz", proxy.getClass().getName());
  CPPUNIT_ASSERT_EQUAL("ERROR: zzz: abc", proxy.what());
}

void
sk::util::test::ExceptionProxyTest::
test_wraps_unknown_exception()
{
  sk::util::ExceptionProxy proxy("zzz");

  CPPUNIT_ASSERT_EQUAL("<UNKNOWN>#zzz", proxy.getClass().getName());
  CPPUNIT_ASSERT_EQUAL("ERROR: zzz", proxy.what());
}
