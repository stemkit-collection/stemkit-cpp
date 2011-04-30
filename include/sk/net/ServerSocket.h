/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_SERVERSOCKET_H_
#define _SK_NET_SERVERSOCKET_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/net/Socket.h>

namespace sk {
  namespace net {
    class InetAddress;
    class InetSocketAddress;
    class DirectedSocket;

    class ServerSocket 
      : public virtual sk::util::Object
    {
      public:
        ServerSocket(const uint16_t port);
        ServerSocket(const uint16_t port, const int backlog);
        ServerSocket(const uint16_t port, const int backlog, const sk::net::InetAddress& bindAddress);
        virtual ~ServerSocket();

        sk::net::Socket accept();
        void close();

        const sk::net::InetSocketAddress& endpoint() const;
        const sk::net::InetAddress& address() const;
        const uint16_t port() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
    
      private:
        ServerSocket(const ServerSocket& other);
        ServerSocket& operator = (const ServerSocket& other);

        void setup(const int backlog);

        sk::util::Holder<sk::net::InetSocketAddress>::Direct _endpointHolder;
        sk::util::Holder<sk::net::DirectedSocket>::Direct _socketHolder;
    };
  }
}

#endif /* _SK_NET_SERVERSOCKET_H_ */
