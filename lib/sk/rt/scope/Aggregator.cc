/*  vim:sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/scope/Arbitrator.h>
#include <sk/rt/Locker.cxx>
#include "scope/Config.h"
#include "scope/NullArbitrator.h"

sk::rt::scope::Aggregator::
Aggregator()
  : _configHolderHolder(new sk::util::Holder<Config>(new Config)),
    _arbitratorHolder(new scope::NullArbitrator)
{
}

sk::rt::scope::Aggregator::
Aggregator(const sk::rt::scope::Aggregator& other)
  : _configHolderHolder(other._configHolderHolder.get()),
    _arbitratorHolder(other._arbitratorHolder)
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

void
sk::rt::scope::Aggregator::
setArbitrator(scope::Arbitrator* arbitrator)
{
  _arbitratorHolder.set(arbitrator);
}

sk::rt::scope::Arbitrator&
sk::rt::scope::Aggregator::
getArbitrator() const
{
  return _arbitratorHolder.get();
}

sk::rt::scope::Aggregator&
sk::rt::scope::Aggregator::
obtain(const sk::util::String& name)
{
  sk::rt::Locker<sk::rt::scope::Arbitrator> locker(_arbitratorHolder.get());
  registry::iterator iterator = _subordinates.find(name);
  if(iterator != _subordinates.end()) {
    return iterator->second;
  }
  ensureOwnConfigHolder();
  return _subordinates.insert(std::make_pair(name, Aggregator(*this))).first->second;
}

void
sk::rt::scope::Aggregator::
ensureOwnConfigHolder()
{
  if(_configHolderHolder.isOwner() == false) {
    _configHolderHolder.set(new sk::util::Holder<Config>(_configHolderHolder.get().get()));
  }
}

void
sk::rt::scope::Aggregator::
ensureOwnConfig()
{
  if(_configHolderHolder.get().isOwner() == false) {
    _configHolderHolder.get().set(new Config(_configHolderHolder.get().get()));
  }
}

const sk::rt::scope::IConfig&
sk::rt::scope::Aggregator::
getConfig() const
{
  return _configHolderHolder.get().get();
}

sk::rt::scope::IConfig&
sk::rt::scope::Aggregator::
getConfigForUpdate()
{
  ensureOwnConfigHolder();
  ensureOwnConfig();

  return _configHolderHolder.get().get();
}

int
sk::rt::scope::Aggregator::
size() const
{
  return _subordinates.size();
}
