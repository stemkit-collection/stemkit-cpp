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

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class ConnectException 
      : public virtual sk::util::Object
    {
      public:
        ConnectException();
        virtual ~ConnectException();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        ConnectException(const ConnectException& other);
        ConnectException& operator = (const ConnectException& other);
    };
  }
}

#endif /* _SK_NET_CONNECTEXCEPTION_H_ */
