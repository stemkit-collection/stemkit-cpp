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
#include <sk/util/Strings.h>

#include <sk/util/ExceptionProxy.h>

static const sk::util::String __className("sk::util::ExceptionProxy");

namespace {
  const sk::util::String makeClassName(const sk::util::String& name, const sk::util::Strings& strings) {
    return (sk::util::Strings(name) << strings).join("#");
  }
}

sk::util::ExceptionProxy::
ExceptionProxy(const sk::util::Strings& strings, sk::util::Exception& exception)
  : sk::util::Exception(strings, exception), _originalClassName(makeClassName(exception.getClass().getName(), strings))
{
}

sk::util::ExceptionProxy::
ExceptionProxy(const sk::util::Strings& strings, std::exception& exception)
  : sk::util::Exception(strings + exception.what()), _originalClassName(makeClassName("std::exception", strings))
{
}

sk::util::ExceptionProxy::
ExceptionProxy(const sk::util::Strings& strings)
  : sk::util::Exception(strings), _originalClassName(makeClassName("<UNKNOWN>", strings))
{
}

sk::util::ExceptionProxy::
~ExceptionProxy() throw()
{
}

const sk::util::Class
sk::util::ExceptionProxy::
getClass() const
{
  return sk::util::Class(_originalClassName);
}
