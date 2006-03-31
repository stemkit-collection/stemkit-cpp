/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_CPPUNIT_SINGLELINEOUTPUTTER_
#define _SK_CPPUNIT_SINGLELINEOUTPUTTER_

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

namespace sk {
  namespace cppunit {
    class SingleLineOutputter 
      : public CppUnit::CompilerOutputter 
    {
      public:
        SingleLineOutputter(CppUnit::TextUi::TestRunner& runner);

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

#endif /* _SK_CPPUNIT_SINGLELINEOUTPUTTER_ */
