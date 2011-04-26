/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_INETADDRESSFACTORY_H_
#define _SK_NET_INETADDRESSFACTORY_H_

#include <sk/util/Object.h>
#include <sk/util/ArrayList.hxx>
#include <sk/rt/ReentrantReadWriteLock.h>
#include <vector>

namespace sk {
  namespace net {
    class InetAddress;

    class InetAddressFactory 
      : public virtual sk::util::Object
    {
      public:
        InetAddressFactory();
        virtual ~InetAddressFactory();

        sk::net::InetAddress& findOrCreateByAddress(const std::vector<int>& components);
        const sk::net::InetAddress& findOrCreateByName(const sk::util::String& name);
        const sk::net::InetAddress& findOrCreateLocalHost();

        static sk::net::InetAddressFactory& instance();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        InetAddressFactory(const InetAddressFactory& other);
        InetAddressFactory& operator = (const InetAddressFactory& other);

        sk::util::ArrayList<sk::net::InetAddress> _cache;
        sk::rt::ReentrantReadWriteLock _lock;
    };
  }
}

#endif /* _SK_NET_INETADDRESSFACTORY_H_ */
