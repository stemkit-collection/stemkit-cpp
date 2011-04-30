/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP4_DIRECTEDSOCKET_H_
#define _SK_NET_IP4_DIRECTEDSOCKET_H_

#include "../DirectedSocket.h"
#include <sk/util/Holder.hxx>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace sk {
  namespace net {
    namespace ip4 {
      class DirectedSocket 
        : public virtual sk::net::DirectedSocket
      {
        public:
          DirectedSocket(const uint32_t number, const uint16_t port);
          DirectedSocket(const struct sockaddr_in& address, const int socket);
          virtual ~DirectedSocket();

          // sk::net::DirectedSocket implementation.
          void bind() const;
          void listen(int backlog) const;
          void connect() const;
          sk::net::DirectedSocket* accept() const;

          // sk::net::DirectedSocket implementation.
          const uint16_t port() const;
          sk::net::InetAddress& address() const;
          const sk::net::InetSocketAddress localEndpoint() const;

          // sk::net::DirectedSocket implementation.
          sk::io::InputStream& inputStream() const;
          sk::io::OutputStream& outputStream() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          DirectedSocket(const DirectedSocket& other);
          DirectedSocket& operator = (const DirectedSocket& other);

          const struct sockaddr_in _address;
          const int _socket;
          mutable sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
          mutable sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
      };
    }
  }
}

#endif /* _SK_NET_IP4_DIRECTEDSOCKET_H_ */
