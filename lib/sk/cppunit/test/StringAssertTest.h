/*  vim: set sw=4:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_CPPUNIT_TEST_STRINGASSERTTEST_H_
#define _SK_CPPUNIT_TEST_STRINGASSERTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
    namespace cppunit {
        namespace test {
            class StringAssertTest
                : public CppUnit::TestFixture
            {
                CPPUNIT_TEST_SUITE(sk::cppunit::test::StringAssertTest);
                    CPPUNIT_TEST(testBothStdStrings);
                    CPPUNIT_TEST(testBothCharPointers);
                    CPPUNIT_TEST(testBothSkUtilStrings);
                    CPPUNIT_TEST(testStdStringSkUtilString);
                    CPPUNIT_TEST(testCharPointerSkUtilString);
                    CPPUNIT_TEST(testCharPointerStdString);
                    CPPUNIT_TEST(testSkUtilStringCharPointer);
                    CPPUNIT_TEST(testCharPointerNullPointer);
                    CPPUNIT_TEST(testNullPointerCharPointer);
                    CPPUNIT_TEST(testNullPointerStdString);
                    CPPUNIT_TEST(testStdStringNullPointer);
                    CPPUNIT_TEST(testBothNullPointers);
                CPPUNIT_TEST_SUITE_END();

                public:
                    StringAssertTest();
                    virtual ~StringAssertTest();

                    void setUp();
                    void tearDown();

                    void testBothStdStrings();
                    void testBothCharPointers();
                    void testBothSkUtilStrings();
                    void testStdStringSkUtilString();
                    void testCharPointerSkUtilString();
                    void testCharPointerStdString();
                    void testSkUtilStringCharPointer();
                    void testCharPointerNullPointer();
                    void testNullPointerCharPointer();
                    void testNullPointerStdString();
                    void testStdStringNullPointer();
                    void testBothNullPointers();

                private:
                    StringAssertTest(const StringAssertTest& other);
                    StringAssertTest& operator = (const StringAssertTest& other);
            };
        }
    }
}

#endif /* _SK_CPPUNIT_TEST_STRINGASSERTTEST_H_ */
