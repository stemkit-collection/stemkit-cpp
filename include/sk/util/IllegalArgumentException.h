/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_ILLEGALARGUMENTEXCEPTION_H_
#define _SK_UTIL_ILLEGALARGUMENTEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class IllegalArgumentException 
      : public virtual sk::util::Exception
    {
      public:
        IllegalArgumentException(const sk::util::String& message);
        IllegalArgumentException(const sk::util::String& message, const sk::util::Strings& details);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        IllegalArgumentException& operator = (const IllegalArgumentException& other);
    };
  }
}

#endif /* _SK_UTIL_ILLEGALARGUMENTEXCEPTION_H_ */
