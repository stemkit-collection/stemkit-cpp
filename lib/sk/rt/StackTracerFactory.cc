/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/StackTracerFactory.h>

static const sk::util::String __className("sk::rt::StackTracerFactory");

sk::rt::StackTracerFactory::
StackTracerFactory()
{
}

sk::rt::StackTracerFactory::
~StackTracerFactory()
{
}

const sk::util::Class
sk::rt::StackTracerFactory::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::Object*
sk::rt::StackTracerFactory::
clone() const
{
  return new sk::rt::StackTracerFactory(*this);
}
