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

    class ServerSocket 
      : public virtual sk::util::Object
    {
      public:
        ServerSocket();
        ServerSocket(int port);
        ServerSocket(int port, int backlog);
        ServerSocket(int port, int backlog, const sk::net::InetAddress& bindAddress);
        virtual ~ServerSocket();

        sk::net::Socket accept();
        void close();

        void bind(const InetSocketAddress& endpoint);
        void bind(const InetSocketAddress& endpoint, int backlog);
        bool isBound() const;
        int getBacklog() const;

        int getPort() const;
        const sk::net::InetSocketAddress& getSocketAddress() const;
        const sk::net::InetAddress& getInetAddress() const;

        bool getReuseAddress() const;
        void setReuseAddress(bool state);

        int getReceiveBufferSize() const;
        void setReceiveBufferSize(int size);

        int getSoTimeout() const;
        void setSoTimeout(int timeout);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
    
      private:
        ServerSocket(const ServerSocket& other);
        ServerSocket& operator = (const ServerSocket& other);

        void ensureBound() const;

        sk::util::Holder<sk::net::InetSocketAddress>::Copying _endpointHolder;
        int _backlog;
        int _socket;
    };
  }
}

#endif /* _SK_NET_SERVERSOCKET_H_ */
