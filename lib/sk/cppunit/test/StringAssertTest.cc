/*  vim: set sw=4:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "StringAssertTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::cppunit::test::StringAssertTest);

sk::cppunit::test::StringAssertTest::
StringAssertTest()
{
}

sk::cppunit::test::StringAssertTest::
~StringAssertTest()
{
}

void
sk::cppunit::test::StringAssertTest::
setUp()
{
}

void
sk::cppunit::test::StringAssertTest::
tearDown()
{
}

void
sk::cppunit::test::StringAssertTest::
testBothStdStrings()
{
    try {
        CPPUNIT_ASSERT_EQUAL(std::string("aaa"), std::string("bbb"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testBothCharPointers()
{
    try {
        CPPUNIT_ASSERT_EQUAL("aaa", "bbb");
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testBothSkUtilStrings()
{
    try {
        CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), sk::util::String("bbb"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testStdStringSkUtilString()
{
    try {
        CPPUNIT_ASSERT_EQUAL(std::string("aaa"), sk::util::String("bbb"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testCharPointerSkUtilString()
{
    try {
        CPPUNIT_ASSERT_EQUAL("aaa", sk::util::String("bbb"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testCharPointerStdString()
{
    try {
        CPPUNIT_ASSERT_EQUAL("aaa", std::string("bbb"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testSkUtilStringCharPointer()
{
    try {
        CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), "bbb");
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"bbb\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testCharPointerNullPointer()
{
    try {
        CPPUNIT_ASSERT_EQUAL("aaa", 0);
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : <null_ptr>", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testNullPointerCharPointer()
{
    try {
        CPPUNIT_ASSERT_EQUAL(0, "aaa");
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: <null_ptr>", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"aaa\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testNullPointerStdString()
{
    try {
        CPPUNIT_ASSERT_EQUAL(0, std::string("aaa"));
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: <null_ptr>", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : \"aaa\"", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testStdStringNullPointer()
{
    try {
        CPPUNIT_ASSERT_EQUAL(std::string("aaa"), 0);
        CPPUNIT_FAIL("Must fail");
    }
    catch(const CPPUNIT_NS::Exception& exception) {
        CPPUNIT_ASSERT_EQUAL(2, exception.message().detailCount());
        CPPUNIT_ASSERT_EQUAL("Expected: \"aaa\"", exception.message().detailAt(0));
        CPPUNIT_ASSERT_EQUAL("Actual  : <null_ptr>", exception.message().detailAt(1));
    }
}

void
sk::cppunit::test::StringAssertTest::
testBothNullPointers()
{
    CPPUNIT_ASSERT_EQUAL(0, 0);
}
