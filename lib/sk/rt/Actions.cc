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
#include <sk/util/StandardException.h>
#include <sk/util/UnknownException.h>
#include <sk/util/CompoundException.h>
#include <sk/util/ArrayList.cxx>

#include <sk/rt/Actions.h>

static const sk::util::String __className("sk::rt::Actions");

sk::rt::Actions::Item::
Item(const sk::util::String& label)
  : sk::util::String(label)
{
}

sk::rt::Actions::
Actions(bool reverse)
  : _scope(__className), _reverse(reverse)
{
}

sk::rt::Actions::
~Actions()
{
  performIgnoreErrors();
}

const sk::util::Class
sk::rt::Actions::
getClass() const
{
  return sk::util::Class(__className);
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

int
sk::rt::Actions::
size() const
{
  return _items.size();
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
        _exceptions.add(new sk::util::StandardException(item, exception));
      }
      catch(const std::string& exception) {
        _exceptions.add(new sk::util::Exception(sk::util::Strings(item) << exception));
      }
      catch(...) {
        _exceptions.add(new sk::util::UnknownException(item));
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

int
sk::rt::Actions::
performIgnoreErrors()
{
  runActionsCollectExceptions();
  int number_of_errors = _exceptions.size();
  _exceptions.clear();
  finalize();

  return number_of_errors;
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

  if(_exceptions.isEmpty() == false) {
    sk::rt::Actions cleanupActions;
    cleanupActions.add(SK_METHOD, _exceptions, &sk::util::ArrayList<sk::util::Exception>::clear);
    throw sk::util::CompoundException(_exceptions);
  }
}

void
sk::rt::Actions::
clear()
{
  _items.clear();
}
