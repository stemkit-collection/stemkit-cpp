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

        static bool raiseUnlessSuccess(const sk::util::String& name, int status, int other = 0);
        int getCode() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        int _code;
    };
  }
}

#define SK_SYSTEM_RAISE_UNLESS_SUCCESS(function, args) sk::util::SystemException::raiseUnlessSuccess(#function, function/**/args)
#define SK_SYSTEM_RAISE_UNLESS_SUCCESS_OR(other, function, args) sk::util::SystemException::raiseUnlessSuccess(#function, function/**/args, other)

#endif /* _SK_UTIL_SYSTEMEXCEPTION_ */
