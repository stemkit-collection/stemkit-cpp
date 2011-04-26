/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_INETADDRESS_H_
#define _SK_NET_INETADDRESS_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

namespace sk {
  namespace net {
    class InetAddress 
      : public virtual sk::util::Object
    {
      public:
        virtual ~InetAddress();

        static InetAddress& getByAddress(const std::vector<int>& components);
        static const InetAddress& getByName(const sk::util::String& name);
        static const InetAddress& getLocalHost();
    
        const std::vector<int>& getAddress() const;
        const sk::util::String& getHostName() const;
        const sk::util::String& getHostName();
        const sk::util::String getCanonicalHostName() const;

        virtual const sk::util::String getHostAddress() const = 0;
        virtual bool isLoopbackAddress() const = 0;
        virtual bool isAnyLocalAddress() const = 0;
        virtual bool isMulticastAddress() const = 0;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;

      protected:
        InetAddress(const std::vector<int>& components);
        InetAddress(const std::vector<int>& components, const sk::util::String& name);
        InetAddress(const InetAddress& other);
        InetAddress& operator = (const InetAddress& other);

      private:
        std::vector<int> _address;
        sk::util::String _hostName;
        bool _resolved;
    };
  }
}

#endif /* _SK_NET_INETADDRESS_H_ */
