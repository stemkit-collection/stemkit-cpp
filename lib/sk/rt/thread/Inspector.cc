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

#include "Inspector.h"
#include <sstream>

static const sk::util::Class __class("sk::rt::thread::Inspector");

sk::rt::thread::Inspector::
Inspector(const thread::Generic& thread)
  : _thread(thread)
{
}

sk::rt::thread::Inspector::
~Inspector()
{
}

const sk::util::Class
sk::rt::thread::Inspector::
getClass() const
{
  return __class;
}

const sk::util::String
sk::rt::thread::Inspector::
inspect() const
{
  std::stringstream stream;

  stream << '<'
    << _thread.getClass().getName() << ": "
    << "name=" << _thread.getName().inspect() << ", "
    << "id=" << _thread.getId() << ", "
    << "main?=" << std::boolalpha << _thread.isMain() << ", "
    << "detached?=" << std::boolalpha << _thread.isDetached() << ", "
    << "state=" << _thread.getState().inspect()
  << '>';

  return stream.str();
}
