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

#include <sk/rt/action/Item.h>

static const sk::util::String __className("sk::rt::action::Item");

sk::rt::action::Item::
Item(const sk::util::String& label)
  : _label(label)
{
}

sk::rt::action::Item::
~Item()
{
}

const sk::util::Class
sk::rt::action::Item::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String&
sk::rt::action::Item::
getLabel() const
{
  return _label;
}
