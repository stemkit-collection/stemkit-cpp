/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "InetAddressFactory.h"

#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/SystemException.h>
#include <sk/rt/Locker.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/ip6/InetAddress.h>
#include <sk/net/UnknownHostException.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static const sk::util::String __className("sk::net::InetAddressFactory");

sk::net::InetAddressFactory::
InetAddressFactory()
{
}

sk::net::InetAddressFactory::
~InetAddressFactory()
{
}

sk::net::InetAddressFactory&
sk::net::InetAddressFactory::
instance()
{
  static InetAddressFactory factory;
  return factory;
}

const sk::util::Class
sk::net::InetAddressFactory::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  void create_by_address(const sk::util::bytes& components, sk::util::Holder<sk::net::InetAddress>& holder) {
    for(int counter = 0; holder.isEmpty() == true; ++counter) {
      try {
        switch(counter) {
          case 0:
            holder.set(new sk::net::ip4::InetAddress(components));
            return;

          case 1:
            holder.set(new sk::net::ip6::InetAddress(components));
            return;
        }
      }
      catch(...) {
        continue;
      }
      throw sk::net::UnknownHostException("Unsupported IP address format", components.inspect());
    }
  }

  struct ComponentsSelector : public virtual sk::util::Selector<sk::net::InetAddress> {
    ComponentsSelector(const sk::util::bytes& components)
      : _components(components) {}

    bool assess(const sk::net::InetAddress& address) const {
      return address.getAddress() == _components;
    }
    const sk::util::bytes& _components;
  };
}

sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateByAddress(const sk::util::bytes& components)
{
  sk::util::Holder<sk::net::InetAddress> addressHolder;

  // sk::rt::Locker readLocker(_lock.readLock());
  if(_cache.find(addressHolder, ComponentsSelector(components)) == false) {
    // sk::rt::Locker writeLocker(_lock.writeLock());
    if(_cache.find(addressHolder, ComponentsSelector(components)) == false) {
      create_by_address(components, addressHolder);
      _cache.add(addressHolder.release());
    }
  }
  return addressHolder.getMutable();
}

namespace {
  void create_by_name(const sk::util::String& name, sk::util::Holder<sk::net::InetAddress>& holder) {
    struct addrinfo hints = { 0 };
    struct addrinfo* items = 0;

    hints.ai_family = PF_UNSPEC;
    hints.ai_flags = AI_ADDRCONFIG | AI_CANONNAME;

    int status = getaddrinfo(name.getChars(), 0, &hints, &items);
    if(status != 0) {
      throw sk::net::UnknownHostException(gai_strerror(status), name);
    }
    for(struct addrinfo* item = items; item != 0; item = item->ai_next) {
      for(int counter = 0; holder.isEmpty() == true; ++counter) {
        try {
          switch(counter) {
            case 0:
              holder.set(new sk::net::ip4::InetAddress(name, *item));
              freeaddrinfo(items);
              return;

            case 1:
              holder.set(new sk::net::ip6::InetAddress(name, *item));
              freeaddrinfo(items);
              return;
          }
        }
        catch(const std::exception& exception) {
          continue;
        }
        int family = item->ai_family;
        freeaddrinfo(items);
        throw sk::net::UnknownHostException(sk::util::Strings("Unsupported address family") << sk::util::String::valueOf(family), name);
      }
    }
    freeaddrinfo(items);
  }

  struct NameSelector : public virtual sk::util::Selector<sk::net::InetAddress> {
    NameSelector(const sk::util::String& name)
      : _name(name) {}

    bool assess(const sk::net::InetAddress& address) const {
      return address.getHostAddress().equals(_name) || address.getHostName().equals(_name);
    }
    const sk::util::String& _name;
  };
}

const sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateByName(const sk::util::String& name)
{
  sk::util::Holder<sk::net::InetAddress> addressHolder;

  // sk::rt::Locker readLocker(_lock.readLock());
  if(_cache.find(addressHolder, NameSelector(name)) == false) {
    // sk::rt::Locker writeLocker(_lock.writeLock());
    if(_cache.find(addressHolder, NameSelector(name)) == false) {
      create_by_name(name, addressHolder);
      _cache.add(addressHolder.release());
    }
  }
  return addressHolder.getMutable();
}

const sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateLocalHost()
{
  char buffer[512];
  if(gethostname(buffer, sizeof(buffer)) == -1) {
    throw sk::rt::SystemException("gethostname");
  }
  return findOrCreateByName(buffer);
}
