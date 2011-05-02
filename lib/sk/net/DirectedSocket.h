/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_DIRECTEDSOCKET_H_
#define _SK_NET_DIRECTEDSOCKET_H_

#include <sk/util/Object.h>
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>
#include <sk/net/InetSocketAddress.h>
#include <sk/net/ConfigurableSocket.h>

#include <vector>

namespace sk {
  namespace net {
    class InetAddress;

    class DirectedSocket 
      : public virtual sk::net::ConfigurableSocket
    {
      public:
        virtual void bind() const = 0;
        virtual void listen(const int backlog) const = 0;
        virtual void connect() const = 0;
        virtual sk::net::DirectedSocket* accept() const = 0;
        virtual void sendto(const std::vector<char>& data, const sk::net::InetSocketAddress& endpoint) const = 0;
        virtual const sk::net::InetSocketAddress recvfrom(std::vector<char>& data) const = 0;

        virtual const uint16_t port() const = 0;
        virtual sk::net::InetAddress& address() const = 0;
        virtual const sk::net::InetSocketAddress localEndpoint() const = 0;

        virtual sk::io::InputStream& inputStream() const = 0;
        virtual sk::io::OutputStream& outputStream() const = 0;
    };
  }
}

#endif /* _SK_NET_DIRECTEDSOCKET_H_ */
