/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_TESTS_LOCKERTEST_H_
#define _SK_RT_THREAD_TESTS_LOCKERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/Locker.h>
#include <sk/rt/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class LockerTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::LockerTest);
            CPPUNIT_TEST(testStatementScope);
            CPPUNIT_TEST(testBlockScope);
            CPPUNIT_TEST(testCopying);
            CPPUNIT_TEST(testReturning);
            CPPUNIT_TEST(testThrowing);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            LockerTest();
            virtual ~LockerTest();
        
            void setUp();
            void tearDown();
            void testStatementScope();
            void testBlockScope();
            void testCopying();
            void testReturning();
            void testThrowing();
        
          private:
            LockerTest(const LockerTest& other);
            LockerTest& operator = (const LockerTest& other);

            const sk::rt::Locker locker_originator();
            void locker_pitcher();

            sk::util::Holder<sk::rt::Mutex> _mutexHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_LOCKERTEST_H_ */
