/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_INETSOCKETADDRESS_H_
#define _SK_NET_INETSOCKETADDRESS_H_

#include <sk/net/SocketAddress.h>
#include <sk/net/InetAddress.h>

namespace sk {
  namespace net {
    class InetSocketAddress 
      : public sk::net::SocketAddress
    {
      public:
        InetSocketAddress(const sk::net::InetAddress& address, uint16_t port);
        InetSocketAddress(const sk::util::String& hostname, uint16_t port);
        InetSocketAddress(uint16_t port);
        virtual ~InetSocketAddress();

        uint16_t getPort() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        InetSocketAddress(const InetSocketAddress& other);
        InetSocketAddress& operator = (const InetSocketAddress& other);

        const uint16_t _port;
    };
  }
}

#endif /* _SK_NET_INETSOCKETADDRESS_H_ */
