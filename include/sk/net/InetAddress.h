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
#include <sk/util/bytes.h>

namespace sk {
  namespace net {
    class InetAddress 
      : public virtual sk::util::Object
    {
      public:
        virtual ~InetAddress();

        static InetAddress& getByAddress(const sk::util::bytes& components);
        static const InetAddress& getByName(const sk::util::String& name);
        static const InetAddress& getLocalHost();

        bool isResolved() const;
        const sk::util::bytes& getAddress() const;
        const sk::util::String getHostName();
        const sk::util::String getCanonicalHostName() const;

        virtual const sk::util::String resolve() const = 0;
        virtual const sk::util::String getHostAddress() const = 0;
        virtual bool isLoopbackAddress() const = 0;
        virtual bool isAnyLocalAddress() const = 0;
        virtual bool isMulticastAddress() const = 0;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;

      protected:
        InetAddress(const sk::util::bytes& components);
        InetAddress(const sk::util::bytes& components, const sk::util::String& name);
        InetAddress(const InetAddress& other);
        InetAddress& operator = (const InetAddress& other);

      private:
        sk::util::bytes _address;
        sk::util::String _hostName;
        bool _resolved;
    };
  }
}

#endif /* _SK_NET_INETADDRESS_H_ */
