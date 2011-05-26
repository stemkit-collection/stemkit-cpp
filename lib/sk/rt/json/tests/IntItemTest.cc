/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "IntItemTest.h"
#include <sk/rt/json/IntItem.h>
#include <sk/util/MissingResourceException.h>
#include <sk/util/IllegalArgumentException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::json::tests::IntItemTest);

sk::rt::json::tests::IntItemTest::
IntItemTest()
{
}

sk::rt::json::tests::IntItemTest::
~IntItemTest()
{
}

void
sk::rt::json::tests::IntItemTest::
setUp()
{
}

void
sk::rt::json::tests::IntItemTest::
tearDown()
{
}

void
sk::rt::json::tests::IntItemTest::
test_raises_exception_on_non_present()
{
  Json::Value root;
  sk::rt::json::IntItem value(root, "some-value");
  CPPUNIT_ASSERT_THROW(value.get(), sk::util::MissingResourceException);
}

void
sk::rt::json::tests::IntItemTest::
test_bad_convert_raises_argument_error()
{
  Json::Value root;
  root["some-value"] = "64";
  sk::rt::json::IntItem value(root, "some-value");

  CPPUNIT_ASSERT_THROW(value.get(), sk::util::IllegalArgumentException);
}

void
sk::rt::json::tests::IntItemTest::
test_succeeds_on_present_attribute()
{
  Json::Value root;
  root["some-value"] = 59;
  sk::rt::json::IntItem value(root, "some-value");

  CPPUNIT_ASSERT_EQUAL(59, value.get());
}
