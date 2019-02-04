/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_IMMUTABLEOBJECTEXCEPTION_
#define _SK_UTIL_IMMUTABLEOBJECTEXCEPTION_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class ImmutableObjectException
      : public sk::util::Exception
    {
      public:
        ImmutableObjectException(const sk::util::String& message);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_IMMUTABLEOBJECTEXCEPTION_ */
