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
          DirectedSocket(uint32_t number, uint16_t port);
          DirectedSocket(const struct sockaddr_in address, int socket);
          virtual ~DirectedSocket();

          // sk::net::DirectedSocket implementation.
          void bind() const;
          void listen(int backlog) const;
          void connect() const;
          sk::net::DirectedSocket* accept() const;
          uint16_t getPort() const;
          sk::net::InetAddress& getAddress() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          DirectedSocket(const DirectedSocket& other);
          DirectedSocket& operator = (const DirectedSocket& other);

          const struct sockaddr_in _address;
          const int _socket;
      };
    }
  }
}

#endif /* _SK_NET_IP4_DIRECTEDSOCKET_H_ */
