/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ItemTest.h"
#include <sk/rt/json/IntItem.h>
#include <sk/rt/json/StringItem.h>
#include <sk/rt/json/StringArrayItem.h>
#include <sk/util/MissingResourceException.h>
#include <sk/util/IllegalArgumentException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::json::tests::ItemTest);

sk::rt::json::tests::ItemTest::
ItemTest()
{
}

sk::rt::json::tests::ItemTest::
~ItemTest()
{
}

void
sk::rt::json::tests::ItemTest::
setUp()
{
}

void
sk::rt::json::tests::ItemTest::
tearDown()
{
}

void
sk::rt::json::tests::ItemTest::
test_raises_exception_on_non_present()
{
  Json::Value root;
  sk::rt::json::IntItem intValue(root, "some-value");
  sk::rt::json::StringItem stringValue(root, "some-value");
  sk::rt::json::StringArrayItem stringArrayValue(root, "some-value");

  CPPUNIT_ASSERT_THROW(intValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(stringValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(stringArrayValue.get(), sk::util::MissingResourceException);
}

void
sk::rt::json::tests::ItemTest::
test_bad_convert_raises_argument_error()
{
  Json::Value root;
  root["some-int-value"] = "64";
  root["some-string-value"] = 17;
  sk::rt::json::IntItem intValue(root, "some-int-value");
  sk::rt::json::StringItem stringValue(root, "some-string-value");

  CPPUNIT_ASSERT_THROW(intValue.get(), sk::util::IllegalArgumentException);
  CPPUNIT_ASSERT_THROW(stringValue.get(), sk::util::IllegalArgumentException);
}

void
sk::rt::json::tests::ItemTest::
test_succeeds_on_present_attribute()
{
  Json::Value root;
  root["some-int-value"] = 59;
  root["some-string-value"] = "abc";

  Json::Value array;
  array[0u] = "aaa";
  array[1u] = "bbb";
  array[2u] = "ccc";

  root["some-string-array-value"] = array;

  sk::rt::json::IntItem intValue(root, "some-int-value");
  sk::rt::json::StringItem stringValue(root, "some-string-value");
  sk::rt::json::StringArrayItem stringArrayValue(root, "some-string-array-value");

  CPPUNIT_ASSERT_EQUAL(59, intValue.get());
  CPPUNIT_ASSERT_EQUAL("abc", stringValue.get());
  CPPUNIT_ASSERT_EQUAL("sk::util::Strings[ \"aaa\", \"bbb\", \"ccc\" ]", stringArrayValue.get().inspect());
}
