/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_BINDEXCEPTION_H_
#define _SK_NET_BINDEXCEPTION_H_

#include <sk/net/SocketException.h>

namespace sk {
  namespace net {
    class BindException 
      : public sk::net::SocketException
    {
      public:
        BindException(const uint16_t port);

        const uint16_t getPort() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        const uint16_t _port;
    };
  }
}

#endif /* _SK_NET_BINDEXCEPTION_H_ */
