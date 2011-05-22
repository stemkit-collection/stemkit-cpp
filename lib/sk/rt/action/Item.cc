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
#include <sk/util/Holder.cxx>

#include <sk/rt/action/Item.h>

static const sk::util::String __className("sk::rt::action::Item");

sk::rt::action::Item::
Item(const sk::util::String& label)
  : _labelHolder(new sk::util::String(label))
{
}

sk::rt::action::Item::
Item()
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

sk::util::Strings&
sk::rt::action::Item::
populate(sk::util::Strings& items) const 
{
  if(_labelHolder.isEmpty() == false) {
    items << _labelHolder.get();
  }
  return items;
}
