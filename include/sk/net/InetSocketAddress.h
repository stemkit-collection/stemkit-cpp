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

#include <sk/util/Holder.hxx>
#include <sk/net/SocketAddress.h>

namespace sk {
  namespace net {
    class InetAddress;

    class InetSocketAddress 
      : public sk::net::SocketAddress
    {
      public:
        InetSocketAddress(const sk::net::InetAddress& address, uint16_t port);
        InetSocketAddress(const sk::util::String& hostname, uint16_t port);
        InetSocketAddress(uint16_t port);
        virtual ~InetSocketAddress();

        const sk::net::InetAddress& getAddress() const;
        const sk::util::String getHostName() const;
        uint16_t getPort() const;
        bool isResolved() const;

        int makeBoundSocket() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
    
      private:
        InetSocketAddress& operator = (const InetSocketAddress& other);

        sk::util::Holder<sk::net::InetAddress>::Cloning _addressHolder;
        const uint16_t _port;
    };
  }
}

#endif /* _SK_NET_INETSOCKETADDRESS_H_ */
