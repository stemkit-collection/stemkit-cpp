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

        int getCode() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        int _code;
    };
  }
}

#endif /* _SK_UTIL_SYSTEMEXCEPTION_ */
