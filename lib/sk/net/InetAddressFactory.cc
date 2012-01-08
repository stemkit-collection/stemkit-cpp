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
#include <sk/rt/Locker.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/ip6/InetAddress.h>
#include <sk/net/UnknownHostException.h>
#include <sk/net/SocketException.h>

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
  sk::rt::Locker locker(_lock);
  _cache.clear();
}

namespace {
  struct ByAddressSelectorCreator : public virtual sk::util::Selector<sk::net::InetAddress> {
    ByAddressSelectorCreator(const sk::util::bytes& components, sk::util::Holder<sk::net::InetAddress>& holder)
      : _components(components), _holder(holder) {}

    bool assess(const sk::net::InetAddress& address) const {
      return address.getAddress() == _components;
    }

    void tryIPv4() const {
      _holder.set(new sk::net::ip4::InetAddress(_components));
    }

    void tryIPv6() const {
      _holder.set(new sk::net::ip6::InetAddress(_components));
    }

    void error() const {
      throw sk::net::UnknownHostException("Unsupported IP address format", _components.inspect());
    }

    sk::net::InetAddress* create() const {
      sk::rt::Actions actions;

      actions.addMethod("ip4-a", *this, &ByAddressSelectorCreator::tryIPv4);
      actions.addMethod("ip6-a", *this, &ByAddressSelectorCreator::tryIPv6);
      actions.addMethod("error", *this, &ByAddressSelectorCreator::error);

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

  sk::rt::Locker locker(_lock);
  if(_cache.findMutable(addressHolder, selectorCreator) == false) {
    _cache.add(selectorCreator.create());
  }
  return addressHolder.getMutable();
}

