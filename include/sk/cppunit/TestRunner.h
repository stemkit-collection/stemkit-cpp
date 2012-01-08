/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_CPPUNIT_TESTRUNNER_
#define _SK_CPPUNIT_TESTRUNNER_

#include <cppunit/ui/text/TestRunner.h>

namespace sk {
  namespace cppunit {
    class TestRunner
      : public CppUnit::TextUi::TestRunner
    {
      public:
        TestRunner();
        virtual ~TestRunner();

      private:
        TestRunner(const TestRunner& other);
        TestRunner& operator = (const TestRunner& other);
    };
  }
}

#endif /* _SK_CPPUNIT_TESTRUNNER_ */
