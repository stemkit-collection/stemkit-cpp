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

#include <sk/rt/Actions.h>
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

void 
sk::net::InetAddressFactory::
clearCache()
{
  // sk::util::Locker locker(_lock.writeLock());
  _cache.clear();
}

namespace {
  struct ByAddressSelectorCreator : public virtual sk::util::Selector<sk::net::InetAddress> {
    ByAddressSelectorCreator(const sk::util::bytes& components, sk::util::Holder<sk::net::InetAddress>& holder)
      : _components(components), _holder(holder) {}

    bool assess(const sk::net::InetAddress& address) const {
      return address.getAddress() == _components;
    }

    void tryIp4() const {
      _holder.set(new sk::net::ip4::InetAddress(_components));
    }
    
    void tryIp6() const {
      _holder.set(new sk::net::ip6::InetAddress(_components));
    }

    void error() const {
      throw sk::net::UnknownHostException("Unsupported IP address format", _components.inspect());
    }

    sk::net::InetAddress* create() const {
      sk::rt::Actions actions;

      actions.add("ip4-a", *this, &ByAddressSelectorCreator::tryIp4);
      actions.add("ip6-a", *this, &ByAddressSelectorCreator::tryIp6);
      actions.add("error", *this, &ByAddressSelectorCreator::error);

      actions.performUntilSuccess(true);
      return _holder.release();
    }
    const sk::util::bytes& _components;
    sk::util::Holder<sk::net::InetAddress>& _holder;
  };
}

sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateByAddress(const sk::util::bytes& components)
{
  sk::util::Holder<sk::net::InetAddress> addressHolder;
  ByAddressSelectorCreator selectorCreator(components, addressHolder);

  // sk::rt::Locker readLocker(_lock.readLock());
  if(_cache.find(addressHolder, selectorCreator) == false) {
    // sk::rt::Locker writeLocker(_lock.writeLock());
    if(_cache.find(addressHolder, selectorCreator) == false) {
      _cache.add(selectorCreator.create());
    }
  }
  return addressHolder.getMutable();
}

namespace {
  struct ByNameSelectorCreator : public virtual sk::util::Selector<sk::net::InetAddress> {
    ByNameSelectorCreator(const sk::util::String& name, sk::util::Holder<sk::net::InetAddress>& holder)
      : _name(name), _holder(holder), _items(0) {}

    ~ByNameSelectorCreator() {
      if(_items != 0) {
        freeaddrinfo(_items);
      }
    }

    bool assess(const sk::net::InetAddress& address) const {
      return address.getHostAddress().equals(_name) || address.getHostName().equals(_name);
    }

    sk::net::InetAddress* create() {
      struct addrinfo hints = { 0 };

      hints.ai_family = PF_UNSPEC;
      hints.ai_flags = AI_ADDRCONFIG | AI_CANONNAME;

      int status = getaddrinfo(_name.getChars(), 0, &hints, &_items);
      if(status != 0) {
        throw sk::net::UnknownHostException(gai_strerror(status), _name);
      }
      for(struct addrinfo* item = _items; item != 0; item = item->ai_next) {
        sk::rt::Actions actions;

        actions.add("ip4-n", *this, &ByNameSelectorCreator::tryIp4, *item);
        actions.add("ip6-n", *this, &ByNameSelectorCreator::tryIp6, *item);
        actions.add("error", *this, &ByNameSelectorCreator::error, *item);

        actions.performUntilSuccess(true);
      }
      return _holder.release();
    }

    void tryIp4(const struct addrinfo& item) const {
      _holder.set(new sk::net::ip4::InetAddress(_name, item));
    }

    void tryIp6(const struct addrinfo& item) const {
      _holder.set(new sk::net::ip6::InetAddress(_name, item));
    }

    void error(const struct addrinfo& item) const {
      throw sk::net::UnknownHostException(sk::util::Strings("Unsupported address family") << sk::util::String::valueOf(item.ai_family), _name);
    }

    const sk::util::String& _name;
    sk::util::Holder<sk::net::InetAddress>& _holder;
    struct addrinfo* _items;
  };
}

const sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateByName(const sk::util::String& name)
{
  sk::util::Holder<sk::net::InetAddress> addressHolder;
  ByNameSelectorCreator selectorCreator(name, addressHolder);

  // sk::rt::Locker readLocker(_lock.readLock());
  if(_cache.find(addressHolder, selectorCreator) == false) {
    // sk::rt::Locker writeLocker(_lock.writeLock());
    if(_cache.find(addressHolder, selectorCreator) == false) {
      _cache.add(selectorCreator.create());
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
