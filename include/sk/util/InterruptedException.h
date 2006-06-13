/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INTERRUPTEDEXCEPTION_
#define _SK_UTIL_INTERRUPTEDEXCEPTION_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class InterruptedException
      : public sk::util::Exception
    {
      public:
        InterruptedException(const sk::util::String& message);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_INTERRUPTEDEXCEPTION_ */
