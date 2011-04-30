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

#include <sk/net/AbstractSocket.h>

#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

namespace sk {
  namespace net {
    class ServerSocket;

    class Socket 
      : public sk::net::AbstractSocket
    {
      public:
        Socket(const sk::net::InetSocketAddress& endpoint);
        Socket(const sk::net::InetAddress& address, const uint16_t port);
        Socket(const sk::util::String& host, const uint16_t port);
        virtual ~Socket();

        sk::io::InputStream& inputStream() const;
        sk::io::OutputStream& outputStream() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Socket(sk::net::DirectedSocket* directedSocket);
        Socket& operator = (const Socket& other);

        friend class sk::net::ServerSocket;
    };
  }
}

#endif /* _SK_NET_SOCKET_H_ */
