/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_ABSTRACTSOCKET_H_
#define _SK_NET_ABSTRACTSOCKET_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/net/InetSocketAddress.h>
#include <sk/net/InetAddress.h>

#include <sk/net/ConfigurableSocket.h>
#include <sk/net/DirectedSocket.h>

#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

namespace sk {
  namespace net {
    class AbstractSocket 
      : public virtual sk::net::ConfigurableSocket
    {
      public:
        virtual ~AbstractSocket();
    
        const sk::net::InetSocketAddress& endpoint() const;
        const sk::net::InetAddress& address() const;
        const uint16_t port() const;

        const sk::net::InetSocketAddress& localEndpoint() const;
        const sk::net::InetAddress& localAddress() const;
        const uint16_t localPort() const;

        sk::io::InputStream& inputStream() const;
        sk::io::OutputStream& outputStream() const;

        void close();

        // sk::net::ConfigurableSocket implementation.
        void setReuseAddress(bool state);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      protected:
        AbstractSocket(sk::net::DirectedSocket* directedSocket);
        const sk::net::DirectedSocket& directedSocket() const;

        virtual bool isBound() const = 0;

      private:
        AbstractSocket& operator = (const AbstractSocket& other);

        void ensureBound(const bool state) const;

        sk::util::Holder<sk::net::DirectedSocket>::Sharing _directedSocketHolder;
        mutable sk::util::Holder<sk::net::InetSocketAddress>::Copying _endpointHolder;
        mutable sk::util::Holder<sk::net::InetSocketAddress>::Copying _localEndpointHolder;
    };
  }
}

#endif /* _SK_NET_ABSTRACTSOCKET_H_ */
