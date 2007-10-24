/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/scope/Agregator.h>

sk::rt::scope::Agregator::
Agregator()
  : _configHolderHolder(new sk::util::Holder<Config>(new Config))
{
}

sk::rt::scope::Agregator::
Agregator(const sk::rt::scope::Agregator& other)
  : _configHolderHolder(other._configHolderHolder.get())
{
}

sk::rt::scope::Agregator::
~Agregator()
{
}

const sk::util::Class
sk::rt::scope::Agregator::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Agregator");
}

sk::rt::scope::Agregator&
sk::rt::scope::Agregator::
obtain(const sk::util::String& name)
{
  registry::iterator iterator = _subordinates.find(name);
  if(iterator != _subordinates.end()) {
    return iterator->second;
  }
  return _subordinates.insert(std::make_pair(name, Agregator(*this))).first->second;
}

sk::rt::scope::Config&
sk::rt::scope::Agregator::
getConfig() const
{
  return _configHolderHolder.get().get();
}
