/*  vim: set sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SYSTEMEXIT_
#define _SK_UTIL_SYSTEMEXIT_

#include <string>
#include <exception>

namespace sk {
  namespace util {
    class SystemExit
    {
      public:
        SystemExit(int code);
        SystemExit(int code, const std::string& message);
        SystemExit(const std::string& message);
        SystemExit(int code, const std::exception& exception);
        SystemExit(const std::exception& exception);

        int getCode() const;
        const std::string getMessage() const;

      private:
        int _code;
        const std::string _message;
    };
  }
}

#endif /* _SK_UTIL_SYSTEMEXIT_ */
