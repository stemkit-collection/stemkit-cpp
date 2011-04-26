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
#include <sk/util/MissingResourceException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/net/InetAddress.h>
#include "InetAddressFactory.h"

static const char* __className("sk::net::InetAddress");

sk::net::InetAddress::
InetAddress(const std::vector<int>& components)
  : _address(components), _resolved(false)
{
}

sk::net::InetAddress::
InetAddress(const std::vector<int>& components, const sk::util::String& name)
  : _address(components), _hostName(name), _resolved(true)
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
  return (_resolved == false ? sk::util::String("\?\?\?") : getHostName() ) + '/' + getHostAddress();
}

const std::vector<int>&
sk::net::InetAddress::
getAddress() const
{
  return _address;
}

const sk::util::String&
sk::net::InetAddress::
getHostName() const
{
  if(_resolved == true) {
    return _hostName;
  }
  throw sk::util::MissingResourceException("Unresolved host name");
}

const sk::util::String&
sk::net::InetAddress::
getHostName() 
{
  if(_resolved == true) {
    _hostName = getCanonicalHostName();
    _resolved = true;
  }
  return _hostName;
}

const sk::util::String
sk::net::InetAddress::
getCanonicalHostName() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::net::InetAddress& 
sk::net::InetAddress::
getByAddress(const std::vector<int>& components)
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
