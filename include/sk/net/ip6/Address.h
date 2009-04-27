/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP6_ADDRESS_H_
#define _SK_NET_IP6_ADDRESS_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    namespace ip6 {
      class Address 
        : public virtual sk::util::Object
      {
        public:
          Address();
          virtual ~Address();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Address(const Address& other);
          Address& operator = (const Address& other);
      };
    }
  }
}

#endif /* _SK_NET_IP6_ADDRESS_H_ */