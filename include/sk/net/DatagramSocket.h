/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_DATAGRAMSOCKET_H_
#define _SK_NET_DATAGRAMSOCKET_H_

#include <sk/net/AbstractSocket.h>

namespace sk {
  namespace net {
    class DatagramPacket;

    class DatagramSocket 
      : public sk::net::AbstractSocket
    {
      public:
        DatagramSocket();
        DatagramSocket(const uint16_t port);
        DatagramSocket(const uint16_t port, const sk::net::InetAddress& address);
        DatagramSocket(const sk::net::InetSocketAddress& endpoint);
        virtual ~DatagramSocket();

        void receive(sk::net::DatagramPacket& packet);
        void send(const sk::net::DatagramPacket& packet);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        DatagramSocket(const DatagramSocket& other);
        DatagramSocket& operator = (const DatagramSocket& other);
    };
  }
}

#endif /* _SK_NET_DATAGRAMSOCKET_H_ */
