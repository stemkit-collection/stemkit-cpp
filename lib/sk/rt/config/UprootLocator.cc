/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/UprootLocator.h>
#include <unistd.h>

sk::rt::config::UprootLocator::
UprootLocator(const sk::util::String& item, const sk::util::Pathname& location, const SpotLocator& other)
  : SpotLocator(item, location, figureLocator(item, expandCwd(location), other))
{
}

sk::rt::config::UprootLocator::
UprootLocator(const sk::util::String& item, const sk::util::Pathname& location)
  : SpotLocator(item, location, figureLocator(item, expandCwd(location), SpotLocator::DUMMY))
{
}

sk::rt::config::UprootLocator::
~UprootLocator()
{
}

const sk::rt::config::SpotLocator
sk::rt::config::UprootLocator::
figureLocator(const sk::util::String& item, const sk::util::Pathname& location, const SpotLocator& other)
{
  const sk::util::Pathname parent = location.dirname();
  const sk::util::Pathname grandparent = parent.dirname();

  if(location == parent || parent == ".") {
    if(parent == grandparent) {
      return other;
    }
    return SpotLocator(item, parent, other);
  }
  return SpotLocator(item, parent, figureLocator(item, parent, other));
}

const sk::util::Pathname
sk::rt::config::UprootLocator::
expandCwd(const sk::util::Pathname& pathname)
{
  if(pathname != ".") {
    return pathname;
  }
  char buffer[1024];
  return getcwd(buffer, sizeof(buffer));
}

const sk::util::Class
sk::rt::config::UprootLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::UprootLocator");
}
