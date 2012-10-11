/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_NOROUTETOHOSTEXCEPTION_H_
#define _SK_NET_NOROUTETOHOSTEXCEPTION_H_

#include <sk/net/ConnectException.h>

namespace sk {
  namespace net {
    class NoRouteToHostException 
      : public sk::net::ConnectException
    {
      public:
        NoRouteToHostException(const sk::util::String& host, const uint16_t port);
        ~NoRouteToHostException() throw() {};
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_NET_NOROUTETOHOSTEXCEPTION_H_ */
