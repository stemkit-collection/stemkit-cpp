/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INSUFFICIENTMEMORYEXCEPTION_
#define _SK_UTIL_INSUFFICIENTMEMORYEXCEPTION_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class InsufficientMemoryException
      : public sk::util::Exception
    {
      public:
        InsufficientMemoryException(const sk::util::String& purpose, size_t amount);

        size_t getRequestedAmount() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        size_t _amount;
    };
  }
}

#endif /* _SK_UTIL_INSUFFICIENTMEMORYEXCEPTION_ */
