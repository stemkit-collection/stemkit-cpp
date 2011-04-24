/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_MULTICASTSOCKET_H_
#define _SK_NET_MULTICASTSOCKET_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class MulticastSocket 
      : public virtual sk::util::Object
    {
      public:
        MulticastSocket();
        virtual ~MulticastSocket();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        MulticastSocket(const MulticastSocket& other);
        MulticastSocket& operator = (const MulticastSocket& other);
    };
  }
}

#endif /* _SK_NET_MULTICASTSOCKET_H_ */
