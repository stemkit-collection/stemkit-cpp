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
  Json::Value params;
  sk::rt::json::IntegerItem intValue(params, "some-value");
  sk::rt::json::StringItem stringValue(params, "some-value");
  sk::rt::json::StringArrayItem stringArrayValue(params, "some-value");
  sk::rt::json::PropertiesItem propertiesValue(params, "some-value");
  sk::rt::json::BooleanItem booleanValue(params, "some-value");

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
  Json::Value params;
  params["some-int-value"] = "64";
  params["some-string-value"] = 17;
  sk::rt::json::IntegerItem intValue(params, "some-int-value");
  sk::rt::json::StringItem stringValue(params, "some-string-value");

  CPPUNIT_ASSERT_THROW(intValue.get(), sk::util::IllegalArgumentException);
  CPPUNIT_ASSERT_THROW(stringValue.get(), sk::util::IllegalArgumentException);
}

void
sk::rt::json::tests::ItemTest::
test_succeeds_on_present_attribute()
{
  Json::Value params;
  params["some-int-value"] = 59;
  params["some-string-value"] = "abc";
  params["some-true-value"] = true;
  params["some-false-value"] = false;

  Json::Value array;
  array[0u] = "aaa";
  array[1u] = "bbb";
  array[2u] = "ccc";

  params["some-string-array-value"] = array;

  Json::Value properties;
  properties["p1"] = "uuu";
  properties["p2"] = "zzz";
  properties["p3"] = "aaa";

  params["some-properties-value"] = properties;

  sk::rt::json::IntegerItem intValue(params, "some-int-value");
  sk::rt::json::StringItem stringValue(params, "some-string-value");
  sk::rt::json::StringArrayItem stringArrayValue(params, "some-string-array-value");
  sk::rt::json::PropertiesItem propertiesValue(params, "some-properties-value");
  sk::rt::json::BooleanItem trueValue(params, "some-true-value");
  sk::rt::json::BooleanItem falseValue(params, "some-false-value");

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
  Json::Value params;
  sk::rt::json::IntegerItem intValue(sk::rt::json::IntegerItem(params, "some-int"));
  sk::rt::json::StringItem stringValue(sk::rt::json::StringItem(params, "some-string"));
  sk::rt::json::StringArrayItem stringArrayValue(sk::rt::json::StringArrayItem(params, "some-string-array"));
  sk::rt::json::PropertiesItem propertiesValue(sk::rt::json::PropertiesItem(params, "some-properties"));
  sk::rt::json::BooleanItem booleanValue(sk::rt::json::BooleanItem(params, "some-boolean"));

  CPPUNIT_ASSERT_EQUAL("some-int", intValue.name());
  CPPUNIT_ASSERT_EQUAL("some-string", stringValue.name());
  CPPUNIT_ASSERT_EQUAL("some-string-array", stringArrayValue.name());
  CPPUNIT_ASSERT_EQUAL("some-properties", propertiesValue.name());
  CPPUNIT_ASSERT_EQUAL("some-boolean", booleanValue.name());
}
