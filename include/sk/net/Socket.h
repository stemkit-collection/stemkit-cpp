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
#include <sk/util/Holder.hxx>
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

#include <sk/net/InetSocketAddress.h>
#include <sk/net/InetAddress.h>

namespace sk {
  namespace net {
    class DirectedSocket;
    class InetAddress;
    class ServerSocket;

    class Socket 
      : public virtual sk::util::Object
    {
      public:
        Socket(const sk::net::InetSocketAddress& endpoint);
        Socket(const sk::net::InetAddress& address, int port);
        Socket(const sk::util::String& host, int port);
        virtual ~Socket();

        const sk::net::InetSocketAddress& endpoint() const;
        const sk::net::InetAddress& address() const;
        const uint16_t port() const;

        const sk::net::InetSocketAddress& localEndpoint() const;
        const sk::net::InetAddress& localAddress() const;
        const uint16_t localPort() const;

        sk::io::InputStream& inputStream() const;
        sk::io::OutputStream& outputStream() const;

        void close();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Socket(sk::net::DirectedSocket* directedSocket);
        Socket& operator = (const Socket& other);

        sk::util::Holder<sk::net::DirectedSocket>::Sharing _directedSocketHolder;
        mutable sk::util::Holder<sk::net::InetSocketAddress>::Copying _endpointHolder;
        mutable sk::util::Holder<sk::net::InetSocketAddress>::Copying _localEndpointHolder;

        friend class sk::net::ServerSocket;
    };
  }
}

#endif /* _SK_NET_SOCKET_H_ */
