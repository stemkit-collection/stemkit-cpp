/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_CONNECTEXCEPTION_H_
#define _SK_NET_CONNECTEXCEPTION_H_

#include <sk/net/SocketException.h>

namespace sk {
  namespace net {
    class ConnectException
      : public sk::net::SocketException
    {
      public:
        ConnectException(const sk::util::String& message, const sk::util::String& host, const uint16_t port);
        ConnectException(const sk::util::String& host, const uint16_t port);
        virtual ~ConnectException() throw();

        const uint16_t getPort() const;
        const sk::util::String getHost() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        const uint16_t _port;
        const sk::util::String _host;
    };
  }
}

#endif /* _SK_NET_CONNECTEXCEPTION_H_ */
