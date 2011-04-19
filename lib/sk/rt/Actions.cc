/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/ExceptionProxy.h>
#include <sk/util/ArrayList.cxx>

#include <sk/rt/Actions.h>

static const sk::util::String __className("sk::rt::Actions");

sk::rt::Actions::Item::
Item(const sk::util::String& label)
  : sk::util::String(label)
{
}

sk::rt::Actions::
Actions(const sk::rt::Scope& scope)
  : _scope(scope), _reverse(false)
{
}

sk::rt::Actions::
~Actions()
{
  performIgnoreErrors();
}

void
sk::rt::Actions::
setReverse(bool state)
{
  _reverse = state;
}

bool
sk::rt::Actions::
isReverse() const
{
  return _reverse;
}

const sk::util::Class
sk::rt::Actions::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::Actions::
addItem(Item* item)
{
  _items.add(item);
}

namespace {
  struct GuardingExecutor : public virtual sk::util::Processor<const sk::rt::Actions::Item> {
    GuardingExecutor(sk::util::List<sk::util::Exception>& exceptions)
      : _exceptions(exceptions) {}

    void process(const sk::rt::Actions::Item& item) const {
      try {
        item.invoke();
      }
      catch(const sk::util::Exception& exception) {
        _exceptions.add(new sk::util::ExceptionProxy(item, exception));
      }
      catch(const std::exception& exception) {
        _exceptions.add(new sk::util::ExceptionProxy(item, exception));
      }
      catch(...) {
        _exceptions.add(new sk::util::ExceptionProxy(item));
      }
    }
    sk::util::List<sk::util::Exception>& _exceptions;
  };
}

void
sk::rt::Actions::
runActionsCollectExceptions()
{
  if(_reverse) {
    _items.reverse();
  }
  _items.forEach(GuardingExecutor(_exceptions));
}

void 
sk::rt::Actions::
perform()
{
  runActionsCollectExceptions();
  finalize();
}

void 
sk::rt::Actions::
performIgnoreErrors()
{
  runActionsCollectExceptions();
  _exceptions.clear();
  finalize();
}

void 
sk::rt::Actions::
performThrow(const sk::util::Exception& exception)
{
  _exceptions.add(exception);
  runActionsCollectExceptions();
  finalize();
}

void
sk::rt::Actions::
finalize()
{
  _items.clear();
  int number = _exceptions.size();
  if(number > 0) {
    _exceptions.clear();
    throw sk::util::Exception("There are " + sk::util::String::valueOf(number) + "exceptions collected");
  }
}
