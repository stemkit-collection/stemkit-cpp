/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/config/SpotLocator.h>
#include <sk/rt/config/StreamProcessor.h>

#include <sstream>

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::String& item, const sk::util::String& location, const SpotLocator& other)
  : _item(item), _location(location), _locatorHolder(new SpotLocator(other))
{
}

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::String& location, const SpotLocator& other)
  : _item(other._item), _location(location), _locatorHolder(new SpotLocator(other))
{
}

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::String& item, const sk::util::String& location)
  : _item(item), _location(location)
{
}

sk::rt::config::SpotLocator::
SpotLocator(const SpotLocator& other)
  : _item(other._item), _location(other._location)
{
  if(other._locatorHolder.isEmpty() == false) {
    _locatorHolder.set(new SpotLocator(other._locatorHolder.get()));
  }
}

sk::rt::config::SpotLocator::
~SpotLocator()
{
}

const sk::util::Class
sk::rt::config::SpotLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::SpotLocator");
}

void
sk::rt::config::SpotLocator::
invoke(const StreamProcessor& processor, bool simulate) const
{
  if(_locatorHolder.isEmpty() == false) {
    _locatorHolder.get().invoke(processor, simulate);
  }
  if(simulate == true) {
    std::stringstream stream;
    processor.process(stream, _location);
  }
}
