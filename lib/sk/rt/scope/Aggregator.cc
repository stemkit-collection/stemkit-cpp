/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/scope/Aggregator.h>

sk::rt::scope::Aggregator::
Aggregator()
  : _configHolderHolder(new sk::util::Holder<Config>(new Config))
{
}

sk::rt::scope::Aggregator::
Aggregator(const sk::rt::scope::Aggregator& other)
  : _configHolderHolder(other._configHolderHolder.get())
{
}

sk::rt::scope::Aggregator::
~Aggregator()
{
}

const sk::util::Class
sk::rt::scope::Aggregator::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Aggregator");
}

sk::rt::scope::Aggregator&
sk::rt::scope::Aggregator::
obtain(const sk::util::String& name)
{
  registry::iterator iterator = _subordinates.find(name);
  if(iterator != _subordinates.end()) {
    return iterator->second;
  }
  return _subordinates.insert(std::make_pair(name, Aggregator(*this))).first->second;
}

sk::rt::scope::Config&
sk::rt::scope::Aggregator::
getConfig() const
{
  return _configHolderHolder.get().get();
}

int
sk::rt::scope::Aggregator::
size() const
{
  return _subordinates.size();
}
