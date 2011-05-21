/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "../InetAddressFactory.h"

#include <sk/util/Strings.h>
#include <sk/util/ArrayList.cxx>

#include <sk/rt/Actions.h>
#include <sk/rt/Locker.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/ip6/InetAddress.h>
#include <sk/net/UnknownHostException.h>
#include <sk/net/SocketException.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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
      sk::rt::Actions actions;
      for(struct addrinfo* item = _items; item != 0; item = item->ai_next) {
        actions.addMethod("ip4-n", *this, &ByNameSelectorCreator::tryIPv4, *item);
        actions.addMethod("ip6-n", *this, &ByNameSelectorCreator::tryIPv6, *item);
        actions.addMethod("error", *this, &ByNameSelectorCreator::error, *item);
      }
      actions.performUntilSuccess(true);
      return _holder.release();
    }

    void tryIPv4(const struct addrinfo& item) const {
      _holder.set(new sk::net::ip4::InetAddress(_name, item));
    }

    void tryIPv6(const struct addrinfo& item) const {
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

  sk::rt::Locker locker(_lock);
  if(_cache.findMutable(addressHolder, selectorCreator) == false) {
    _cache.add(selectorCreator.create());
  }
  return addressHolder.getMutable();
}

const sk::net::InetAddress& 
sk::net::InetAddressFactory::
findOrCreateLocalHost()
{
  char buffer[512];
  if(gethostname(buffer, sizeof(buffer)) == -1) {
    throw sk::net::SocketException("gethostname");
  }
  return findOrCreateByName(buffer);
}
