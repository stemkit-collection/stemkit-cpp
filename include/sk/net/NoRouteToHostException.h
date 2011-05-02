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

#include <sk/net/SocketException.h>

namespace sk {
  namespace net {
    class NoRouteToHostException 
      : public sk::net::SocketException
    {
      public:
        NoRouteToHostException(const sk::util::String& host);
        virtual ~NoRouteToHostException() throw();

        const sk::util::String getHost() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        const sk::util::String _host;
    };
  }
}

#endif /* _SK_NET_NOROUTETOHOSTEXCEPTION_H_ */
