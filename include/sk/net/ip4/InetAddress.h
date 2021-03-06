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
#include <sk/util/bytes.h>

struct addrinfo;

namespace sk {
  namespace net {
    namespace ip4 {
      class InetAddress
        : public sk::net::InetAddress
      {
        public:
          InetAddress(const sk::util::String& name, const struct addrinfo& info);
          InetAddress(const sk::util::bytes& components);
          virtual ~InetAddress();

          static sk::net::InetAddress& getLoopbackAddress();
          static sk::net::InetAddress& getAnyLocalAddress();

          static uint32_t toNumber(const sk::util::bytes& components);
          static const sk::util::bytes toComponents(uint32_t number);
          static const sk::util::String toString(const sk::util::bytes& components);

          // sk::net::InetAddress implementation.
          const sk::util::String getHostAddress() const;
          bool isLoopbackAddress() const;
          bool isAnyLocalAddress() const;
          bool isSiteLocalAddress() const;
          bool isMulticastAddress() const;

          // sk::net::InetAddress implementation.
          sk::net::DirectedSocket* directedStreamSocket(const uint16_t port) const;
          sk::net::DirectedSocket* directedDatagramSocket(const uint16_t port) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          sk::util::Object* clone() const;

        protected:
          // sk::net::InetAddress implementation.
          const sk::util::String lookupHostName() const;

        private:
          static const uint32_t toHostOrder(const uint32_t number);
          static const uint32_t toNetworkOrder(const uint32_t number);

          const uint32_t _number;
      };
    }
  }
}

#endif /* _SK_NET_IP4_INETADDRESS_H_ */
