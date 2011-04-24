/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_IP4_INETADDRESS_H_
#define _SK_NET_IP4_INETADDRESS_H_

#include <sk/util/Object.h>

#include <sk/util/String.h>

namespace sk {
  namespace net {
    namespace ip4 {
      class InetAddress
        : public virtual sk::util::Object 
      {
        public:
          InetAddress();
          InetAddress(const InetAddress& other);
          InetAddress(const sk::util::String& spec);
          InetAddress(uint32_t number);
          virtual ~InetAddress();

          static const InetAddress hostname(const sk::util::String& name);
          static const InetAddress ip(const sk::util::String& number);
          static const InetAddress number(uint32_t number);
          static const InetAddress localhost();

          const sk::util::String hostname() const;
          const sk::util::String ip() const;
          uint32_t number() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          InetAddress& operator = (const InetAddress& other);
      };
    }
  }
}

#endif /* _SK_NET_IP4_INETADDRESS_H_ */
