/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SYSTEMEXCEPTION_
#define _SK_UTIL_SYSTEMEXCEPTION_

#include <sk/util/Exception.h>
#include <errno.h>

namespace sk {
  namespace util {
    class SystemException
      : public sk::util::Exception
    {
      public:
        SystemException(const sk::util::String& message);
        SystemException(const sk::util::String& message, int code);
        ~SystemException() throw() {};

        static bool raiseUnlessSuccess(const sk::util::String& statement, int status, int other = 0);
        int getCode() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        int _code;
    };
  }
}

#define SK_SYSTEM_RAISE_UNLESS_SUCCESS(statement) sk::util::SystemException::raiseUnlessSuccess(#statement, statement)
#define SK_SYSTEM_RAISE_UNLESS_SUCCESS_OR(other, statement) sk::util::SystemException::raiseUnlessSuccess(#statement, statement, other)

#endif /* _SK_UTIL_SYSTEMEXCEPTION_ */
