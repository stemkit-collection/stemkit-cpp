/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_TIMEOUTEXCEPTION_H_
#define _SK_RT_TIMEOUTEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace rt {
    class TimeoutException 
      : public sk::util::Exception
    {
      public:
        TimeoutException();
        TimeoutException(const sk::util::String& message);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_RT_TIMEOUTEXCEPTION_H_ */
