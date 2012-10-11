/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_MISSINGRESOURCEEXCEPTION_
#define _SK_UTIL_MISSINGRESOURCEEXCEPTION_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class MissingResourceException
      : public sk::util::Exception
    {
      public:
        MissingResourceException(const sk::util::String& message);
        MissingResourceException(const sk::util::String& message, const sk::util::Strings& details);
        ~MissingResourceException() throw() {};
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_MISSINGRESOURCEEXCEPTION_ */
