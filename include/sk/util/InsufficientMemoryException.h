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
        InsufficientMemoryException(const sk::util::String& purpose, int amount);

        int getRequestedAmount() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        int _amount;
    };
  }
}

#endif /* _SK_UTIL_INSUFFICIENTMEMORYEXCEPTION_ */
