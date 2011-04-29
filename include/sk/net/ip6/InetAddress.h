/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP6_INETADDRESS_H_
#define _SK_NET_IP6_INETADDRESS_H_

#include <sk/net/InetAddress.h>
#include <sk/util/bytes.h>

struct addrinfo;

namespace sk {
  namespace net {
    namespace ip6 {
      class InetAddress 
        : public sk::net::InetAddress
      {
        public:
          InetAddress(const sk::util::String& name, const struct addrinfo& info);
          InetAddress(const sk::util::bytes& components);
          virtual ~InetAddress();
      
          // sk::net::InetAddress implementation.
          const sk::util::String resolveHostName() const;
          const sk::util::String getHostAddress() const;
          bool isLoopbackAddress() const;
          bool isAnyLocalAddress() const;
          bool isSiteLocalAddress() const;
          bool isMulticastAddress() const;

          // sk::net::InetAddress implementation.
          int makeBoundSocket(uint16_t port) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          InetAddress(const InetAddress& other);
          InetAddress& operator = (const InetAddress& other);
      };
    }
  }
}

#endif /* _SK_NET_IP6_INETADDRESS_H_ */
