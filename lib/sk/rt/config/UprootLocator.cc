/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/UprootLocator.h>
#include <sk/rt/Scope.h>

sk::rt::config::UprootLocator::
UprootLocator(const sk::util::String& item, const sk::util::String& location, const SpotLocator& other)
  : SpotLocator(item, location, figure_locator(item, location, other))
{
}

sk::rt::config::UprootLocator::
UprootLocator(const sk::util::String& item, const sk::util::String& location)
  : SpotLocator(item, location, figure_locator(item, location, SpotLocator::DUMMY))
{
}

sk::rt::config::UprootLocator::
~UprootLocator()
{
}

const sk::rt::config::SpotLocator
sk::rt::config::UprootLocator::
figure_locator(const sk::util::String& item, const sk::util::String& location, const SpotLocator& other)
{
  sk::rt::Scope scope("figure_locator");
  scope.info("I") << item.inspect();
  scope.info("L") << location.inspect();

  std::string::size_type index = location.find_last_of('/');
  if(index != std::string::npos) { 
    if(index == 0) {
      return SpotLocator(item, "/", other);
    }
    return UprootLocator(item, location.substr(0, index), other);
  } 
  return other;
}

const sk::util::Class
sk::rt::config::UprootLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::UprootLocator");
}
