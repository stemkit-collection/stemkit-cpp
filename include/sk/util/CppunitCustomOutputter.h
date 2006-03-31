/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_CPPUNITCUSTOMOUTPUTTER_
#define _SK_UTIL_CPPUNITCUSTOMOUTPUTTER_

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

namespace sk {
  namespace util {
    class CppunitCustomOutputter 
      : public CppUnit::CompilerOutputter 
    {
      public:
        CppunitCustomOutputter(CppUnit::TextUi::TestRunner& runner);

      private:
        // CppUnit::CompilerOutputter implementation.
        void printFailureType(CppUnit::TestFailure* failure);
        void printFailedTestName(CppUnit::TestFailure* failure);
        void printFailureMessage(CppUnit::TestFailure* failure);

        const std::string stripNamespace(const std::string& name) const;

        std::ostream& _stream;
    };
  }
}

#endif /* _SK_UTIL_CPPUNITCUSTOMOUTPUTTER_ */
