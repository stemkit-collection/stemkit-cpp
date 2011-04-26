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
#include <sk/util/String.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/stl/inspect.h>

#include <sk/rt/SystemException.h>
#include <sk/rt/Locker.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/ip6/InetAddress.h>
#include <sk/net/UnknownHostException.h>

#include <unistd.h>

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
      throw sk::net::UnknownHostException("Unknown ip address family", sk::util::inspect(components));
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

const sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateByName(const sk::util::String& name)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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
