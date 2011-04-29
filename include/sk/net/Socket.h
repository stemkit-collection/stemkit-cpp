/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_SOCKET_H_
#define _SK_NET_SOCKET_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class DirectedSocket;
    class InetSocketAddress;

    class Socket 
      : public virtual sk::util::Object
    {
      public:
        Socket(sk::net::DirectedSocket* directedSocket, const sk::net::InetSocketAddress& localSocketAddress);
        virtual ~Socket();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Socket& operator = (const Socket& other);
    };
  }
}

#endif /* _SK_NET_SOCKET_H_ */
