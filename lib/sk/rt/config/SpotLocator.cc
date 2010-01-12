/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/MissingResourceException.h>

#include <sk/rt/config/SpotLocator.h>
#include <sk/rt/config/StreamProcessor.h>

#include <memory>
#include <fstream>

const sk::rt::config::SpotLocator sk::rt::config::SpotLocator::DUMMY;
sk::util::Holder<const sk::rt::config::NamedStreamOpener> sk::rt::config::SpotLocator::_streamOpenerHolder;

void
sk::rt::config::SpotLocator::
setStreamOpener(const NamedStreamOpener& opener)
{
  _streamOpenerHolder.set(opener);
}

void
sk::rt::config::SpotLocator::
clearStreamOpener()
{
  _streamOpenerHolder.clear();
}

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::String& item, const sk::util::Pathname& location, const SpotLocator& other)
  : _item(item), _location(location)
{
  if(other.isDummy() == false) {
    _locatorHolder.set(new SpotLocator(other));
  }
}

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::Pathname& location, const SpotLocator& other)
  : _item(other._item), _location(location)
{
  if(other.isDummy() == false) {
    _locatorHolder.set(new SpotLocator(other));
  }
}

sk::rt::config::SpotLocator::
SpotLocator(const sk::util::String& item, const sk::util::Pathname& location)
  : _item(item), _location(location)
{
}

sk::rt::config::SpotLocator::
SpotLocator(const SpotLocator& other)
  : _item(other._item), _location(other._location)
{
  if(other.isDummy() == true) {
    becomeDummy();
  }
  else if(other._locatorHolder.isEmpty() == false) {
    _locatorHolder.set(new SpotLocator(other._locatorHolder.get()));
  }
}

sk::rt::config::SpotLocator::
SpotLocator()
  : _location(".")
{
  becomeDummy();
}

sk::rt::config::SpotLocator::
~SpotLocator()
{
}

void
sk::rt::config::SpotLocator::
becomeDummy()
{
  _locatorHolder.set(*this);
}

bool
sk::rt::config::SpotLocator::
isDummy() const
{
  return (_locatorHolder.isEmpty() == false) && (&_locatorHolder.get() == this);
}

const sk::util::Class
sk::rt::config::SpotLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::SpotLocator");
}

const sk::rt::config::NamedStreamOpener&
sk::rt::config::SpotLocator::
getStreamOpener() const
{
  return _streamOpenerHolder.isEmpty() == true ? *this : _streamOpenerHolder.get() ;
}

void
sk::rt::config::SpotLocator::
invoke(const StreamProcessor& processor) const
{
  if(_locatorHolder.isEmpty() == false) {
    _locatorHolder.get().invoke(processor);
  }
  try {
    std::auto_ptr<std::istream> stream(getStreamOpener().openStream(_location.join(_item)));
    processor.process(*stream, _location);
  }
  catch(const sk::util::MissingResourceException& exception) {}
}

std::istream*
sk::rt::config::SpotLocator::
openStream(const sk::util::Pathname& pathname) const
{
  sk::util::String name(pathname.toString());
  std::auto_ptr<std::ifstream> file_ptr(new std::ifstream(name.getChars()));
  if(file_ptr.get()->good()) {
    return file_ptr.release();
  }
  throw sk::util::MissingResourceException(name);
}
