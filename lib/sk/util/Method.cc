/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/Method.h>

namespace {
  const sk::util::String normalizeName(const sk::util::String& name) {
    int index = name.lastIndexOf(":");
    if(index < 0) {
      return name;
    }
    return name.substring(index + 1);
  }
}

sk::util::Method::
Method(const sk::util::String& name, const sk::util::Class& scope, const bool instance)
  : _name(normalizeName(name)), _scopeName(scope.getName()), _instance(instance)
{
}

sk::util::Method::
~Method()
{
}

const sk::util::Class
sk::util::Method::
getClass() const
{
  return sk::util::Class("sk::util::Method");
}

const sk::util::String
sk::util::Method::
getName() const
{
  return _name;
}

const sk::util::String
sk::util::Method::
getScopeName() const
{
  return _scopeName;
}

const sk::util::String
sk::util::Method::
getFullName() const
{
  return _scopeName + (_instance ? "#" : ".") + _name;
}

const sk::util::String
sk::util::Method::
toString() const
{
  return getFullName() + "()";
}
