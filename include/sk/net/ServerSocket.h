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

#include <sk/net/AbstractSocket.h>
#include <sk/net/Socket.h>

namespace sk {
  namespace net {
    class ServerSocket 
       : public sk::net::AbstractSocket
    {
      public:
        ServerSocket(const uint16_t port);
        ServerSocket(const uint16_t port, const int backlog);
        ServerSocket(const uint16_t port, const int backlog, const sk::net::InetAddress& address);
        virtual ~ServerSocket();

        sk::net::Socket accept();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
    
      private:
        ServerSocket(const ServerSocket& other);
        ServerSocket& operator = (const ServerSocket& other);

        void setup(const int backlog);

        bool _bound;
        int _backlog;
    };
  }
}

#endif /* _SK_NET_SERVERSOCKET_H_ */
