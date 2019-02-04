/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_SOCKETADDRESS_H_
#define _SK_NET_SOCKETADDRESS_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class SocketAddress 
      : public virtual sk::util::Object
    {
      public:
        SocketAddress();
        virtual ~SocketAddress();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        SocketAddress& operator = (const SocketAddress& other);
    };
  }
}

#endif /* _SK_NET_SOCKETADDRESS_H_ */
