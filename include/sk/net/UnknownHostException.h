/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_UNKNOWNHOSTEXCEPTION_H_
#define _SK_NET_UNKNOWNHOSTEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace net {
    class UnknownHostException 
      : public sk::util::Exception
    {
      public:
        UnknownHostException(const sk::util::String& hostid);
        UnknownHostException(const sk::util::Strings& messages, const sk::util::String& hostid);
        ~UnknownHostException() throw() {};
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_NET_UNKNOWNHOSTEXCEPTION_H_ */
