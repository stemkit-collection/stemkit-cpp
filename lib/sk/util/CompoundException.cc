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
#include <sk/util/Strings.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/Holder.cxx>
#include <sk/util/ExceptionProxy.h>

#include <sk/util/CompoundException.h>

static const sk::util::String __className("sk::util::CompoundException");

namespace {
  struct Populator : sk::util::Processor<const sk::util::Exception> {
    Populator(sk::util::List<sk::util::Exception>& list)
      : _list(list) {}

    void process(const sk::util::Exception& exception) const {
      _list.add(new sk::util::ExceptionProxy(sk::util::Strings(), exception));
    }
    sk::util::List<sk::util::Exception>& _list;
  };
}

sk::util::CompoundException::
CompoundException(const sk::util::List<sk::util::Exception>& exceptions)
  : sk::util::Exception(sk::util::Strings("Compound") << sk::util::String::valueOf(exceptions.size()), exceptions.get(0)),
    _listHolder(new sk::util::ArrayList<sk::util::Exception>), _list(_listHolder.getMutable())
{
  exceptions.forEach(Populator(_list));
}

sk::util::CompoundException::
~CompoundException() throw()
{
}

const sk::util::Class
sk::util::CompoundException::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::util::CompoundException::
size() const
{
  return _list.size();
}

const sk::util::Exception&
sk::util::CompoundException::
exceptionAt(int index) const
{
  return _list.get(index);
}
