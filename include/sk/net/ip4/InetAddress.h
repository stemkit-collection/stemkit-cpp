/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP4_INETADDRESS_H_
#define _SK_NET_IP4_INETADDRESS_H_

#include <sk/net/InetAddress.h>
#include <vector>

namespace sk {
  namespace net {
    namespace ip4 {
      class InetAddress
        : public sk::net::InetAddress
      {
        public:
          InetAddress(const std::vector<int>& components);
          virtual ~InetAddress();

          // sk::net::InetAddress implementation.
          const sk::util::String getHostAddress() const;
          bool isLoopbackAddress() const;
          bool isAnyLocalAddress() const;
          bool isMulticastAddress() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          InetAddress& operator = (const InetAddress& other);
          InetAddress(const InetAddress& other);
      };
    }
  }
}

#endif /* _SK_NET_IP4_INETADDRESS_H_ */
