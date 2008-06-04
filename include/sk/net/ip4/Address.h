/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP4_ADDRESS_H_
#define _SK_NET_IP4_ADDRESS_H_

#include <sk/util/Object.h>

#include <sk/util/String.h>

namespace sk {
  namespace net {
    namespace ip4 {
      class Address
        : public virtual sk::util::Object 
      {
        public:
          Address(const sk::util::String& spec);
          Address(uint32_t number);
          Address();
          virtual ~Address();

          static const Address hostname(const sk::util::String& name);
          static const Address ip(const sk::util::String& number);
          static const Address number(uint32_t number);
          static const Address localhost();

          const sk::util::String hostname() const;
          const sk::util::String ip() const;
          uint32_t number() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Address(const Address& other);
          Address& operator = (const Address& other);
      };
    }
  }
}

#endif /* _SK_NET_IP4_ADDRESS_H_ */
