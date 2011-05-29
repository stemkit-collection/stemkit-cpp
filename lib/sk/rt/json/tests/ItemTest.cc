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
#include <sk/util/MissingResourceException.h>
#include <sk/util/IllegalArgumentException.h>

#include <sk/rt/json/IntegerItem.h>
#include <sk/rt/json/StringItem.h>
#include <sk/rt/json/StringArrayItem.h>
#include <sk/rt/json/PropertiesItem.h>
#include <sk/rt/json/BooleanItem.h>

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
  sk::rt::json::IntegerItem intValue(root, "some-value");
  sk::rt::json::StringItem stringValue(root, "some-value");
  sk::rt::json::StringArrayItem stringArrayValue(root, "some-value");
  sk::rt::json::PropertiesItem propertiesValue(root, "some-value");
  sk::rt::json::BooleanItem booleanValue(root, "some-value");

  CPPUNIT_ASSERT_THROW(intValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(stringValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(stringArrayValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(propertiesValue.get(), sk::util::MissingResourceException);
  CPPUNIT_ASSERT_THROW(booleanValue.get(), sk::util::MissingResourceException);
}

void
sk::rt::json::tests::ItemTest::
test_bad_convert_raises_argument_error()
{
  Json::Value root;
  root["some-int-value"] = "64";
  root["some-string-value"] = 17;
  sk::rt::json::IntegerItem intValue(root, "some-int-value");
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
  root["some-true-value"] = true;
  root["some-false-value"] = false;

  Json::Value array;
  array[0u] = "aaa";
  array[1u] = "bbb";
  array[2u] = "ccc";

  root["some-string-array-value"] = array;

  Json::Value properties;
  properties["p1"] = "uuu";
  properties["p2"] = "zzz";
  properties["p3"] = "aaa";

  root["some-properties-value"] = properties;

  sk::rt::json::IntegerItem intValue(root, "some-int-value");
  sk::rt::json::StringItem stringValue(root, "some-string-value");
  sk::rt::json::StringArrayItem stringArrayValue(root, "some-string-array-value");
  sk::rt::json::PropertiesItem propertiesValue(root, "some-properties-value");
  sk::rt::json::BooleanItem trueValue(root, "some-true-value");
  sk::rt::json::BooleanItem falseValue(root, "some-false-value");

  CPPUNIT_ASSERT_EQUAL(59, intValue.get());
  CPPUNIT_ASSERT_EQUAL("abc", stringValue.get());
  CPPUNIT_ASSERT_EQUAL("sk::util::Strings[ \"aaa\", \"bbb\", \"ccc\" ]", stringArrayValue.get().inspect());
  CPPUNIT_ASSERT_EQUAL("{ p1 => \"uuu\", p2 => \"zzz\", p3 => \"aaa\" }", propertiesValue.get().inspect());
  CPPUNIT_ASSERT_EQUAL(true, trueValue.get());
  CPPUNIT_ASSERT_EQUAL(false, falseValue.get());
}

void
sk::rt::json::tests::ItemTest::
test_can_be_copied()
{
  Json::Value root;
  sk::rt::json::IntegerItem intValue(sk::rt::json::IntegerItem(root, "some-int"));
  sk::rt::json::StringItem stringValue(sk::rt::json::StringItem(root, "some-string"));
  sk::rt::json::StringArrayItem stringArrayValue(sk::rt::json::StringArrayItem(root, "some-string-array"));
  sk::rt::json::PropertiesItem propertiesValue(sk::rt::json::PropertiesItem(root, "some-properties"));
  sk::rt::json::BooleanItem booleanValue(sk::rt::json::BooleanItem(root, "some-boolean"));

  CPPUNIT_ASSERT_EQUAL("some-int", intValue.name());
  CPPUNIT_ASSERT_EQUAL("some-string", stringValue.name());
  CPPUNIT_ASSERT_EQUAL("some-string-array", stringArrayValue.name());
  CPPUNIT_ASSERT_EQUAL("some-properties", propertiesValue.name());
  CPPUNIT_ASSERT_EQUAL("some-boolean", booleanValue.name());
}