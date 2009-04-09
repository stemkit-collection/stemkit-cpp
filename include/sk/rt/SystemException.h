/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SYSTEMEXCEPTION_H_
#define _SK_RT_SYSTEMEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace rt {
    class SystemException 
      : public virtual sk::util::Exception
    {
      public:
        SystemException(const sk::util::String& message);
        SystemException(const sk::util::String& message, uint32_t code);

        uint32_t getCode() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        uint32_t _code;
    };
  }
}

#endif /* _SK_RT_SYSTEMEXCEPTION_H_ */
