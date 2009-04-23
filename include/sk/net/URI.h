/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_URI_H_
#define _SK_NET_URI_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class URI 
      : public virtual sk::util::Object
    {
      public:
        URI();
        virtual ~URI();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        URI(const URI& other);
        URI& operator = (const URI& other);
    };
  }
}

#endif /* _SK_NET_URI_H_ */
