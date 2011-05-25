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

sk::rt::Actions::
Actions(bool reverse)
  : _scope(__className), _notice(_scope.notice().isEnabled()), _reverse(reverse)
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
addItem(sk::rt::action::Item* item)
{
  _items.add(item);

  if(_notice == true) {
    sk::util::Strings strings(SK_METHOD_NAME);
    _scope.notice() << item->populate(strings).join(": ");
  }
}

namespace {
  struct GuardingExecutor : public virtual sk::util::Selector<sk::rt::action::Item> {
    GuardingExecutor(const sk::rt::Scope& scope, const bool notice, const bool untilSuccess, sk::util::List<sk::util::Exception>& exceptions)
      : _scope(scope), _notice(notice), _untilSuccess(untilSuccess), _exceptions(exceptions) {}

    bool assess(const sk::rt::action::Item& item) const {
      try {
        if(_notice == true) {
          sk::util::Strings strings("invoke");
          _scope.notice() << item.populate(strings).join(": ");
        }
        item.invoke();
        return _untilSuccess;
      }
      catch(const sk::util::Exception& exception) {
        sk::util::Strings strings;
        saveException(new sk::util::ExceptionProxy(item.populate(strings), exception));
      }
      catch(const std::exception& exception) {
        sk::util::Strings strings;
        saveException(new sk::util::StandardException(item.populate(strings), exception));
      }
      catch(const std::string& exception) {
        sk::util::Strings strings;
        saveException(new sk::util::Exception(item.populate(strings) << exception));
      }
      catch(...) {
        sk::util::Strings strings;
        saveException(new sk::util::UnknownException(item.populate(strings)));
      }
      return false;
    }

    void saveException(sk::util::Exception* exception) const {
      _exceptions.add(exception);
      if(_notice == true) {
        _scope.notice("failure") << exception->getMessage();
      }
    }
    const sk::rt::Scope& _scope;
    const bool _untilSuccess;
    const bool _notice;
    sk::util::List<sk::util::Exception>& _exceptions;
  };
}

bool
sk::rt::Actions::
runActionsCollectExceptions(bool untilSuccess)
{
  if(_reverse) {
    _items.reverse();
  }
  return _items.contains(GuardingExecutor(_scope, _notice, untilSuccess, _exceptions));
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
performUntilSuccess(bool reverseErrors)
{
  bool result = runActionsCollectExceptions(true);
  int number_of_errors = _exceptions.size();
  if(result == true) {
    _exceptions.clear();
  }
  else {
    if(reverseErrors == true) {
      _exceptions.reverse();
    }
  }
  finalize();

  return number_of_errors;
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
    cleanupActions.addMethod(SK_METHOD, _exceptions, &sk::util::ArrayList<sk::util::Exception>::clear);
    throw sk::util::CompoundException(_exceptions);
  }
}

void
sk::rt::Actions::
clear()
{
  _items.clear();
}
