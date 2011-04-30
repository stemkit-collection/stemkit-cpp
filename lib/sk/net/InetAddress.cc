/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/net/InetAddress.h>
#include <sk/net/UnknownHostException.h>
#include "InetAddressFactory.h"

static const char* __className("sk::net::InetAddress");

sk::net::InetAddress::
InetAddress(const sk::util::bytes& components)
  : _address(components), _resolved(false)
{
}

sk::net::InetAddress::
InetAddress(const sk::util::bytes& components, const sk::util::String& name)
  : _address(components), _hostName(name), _resolved(true)
{
}

sk::net::InetAddress::
InetAddress(const InetAddress& other)
  : _address(other._address), _hostName(other._hostName), _resolved(other._resolved)
{
}

sk::net::InetAddress::
~InetAddress()
{
}

const sk::util::Class
sk::net::InetAddress::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::net::InetAddress::
toString() const
{
  if(_resolved == false) {
    return getHostAddress();
  }
  return _hostName + '/' + getHostAddress();
}

const sk::util::bytes&
sk::net::InetAddress::
getAddress() const
{
  return _address;
}

bool
sk::net::InetAddress::
isResolved() const
{
  return _resolved;
}

sk::net::InetAddress&
sk::net::InetAddress::
resolve(bool tolerate)
{
  if(_resolved == false) {
    if(tolerate == true) {
      try {
        _hostName = lookupHostName();
        _resolved = true;
      }
      catch(const sk::net::UnknownHostException& exception) {}
    }
    else {
      _hostName = lookupHostName();
      _resolved = true;
    }
  }
  return *this;
}

const sk::util::String
sk::net::InetAddress::
getHostName() const
{
  return (_resolved == true ? _hostName : getHostAddress());
}

const sk::util::String
sk::net::InetAddress::
getCanonicalHostName() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::net::InetAddress& 
sk::net::InetAddress::
getByAddress(const sk::util::bytes& components)
{
  return InetAddressFactory::instance().findOrCreateByAddress(components);
}

const sk::net::InetAddress& 
sk::net::InetAddress::
getByName(const sk::util::String& name)
{
  return InetAddressFactory::instance().findOrCreateByName(name);
}

const sk::net::InetAddress& 
sk::net::InetAddress::
getLocalHost()
{
  return InetAddressFactory::instance().findOrCreateLocalHost();
}

void
sk::net::InetAddress::
clearCache()
{
  return InetAddressFactory::instance().clearCache();
}
