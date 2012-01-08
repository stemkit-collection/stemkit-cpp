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

#include <sk/rt/json/BooleanItem.h>

static const sk::util::String __className("sk::rt::json::BooleanItem");

sk::rt::json::BooleanItem::
BooleanItem(Json::Value& value, const sk::util::String& name)
  : sk::rt::json::Item(value, name)
{
}

sk::rt::json::BooleanItem::
~BooleanItem()
{
}

const sk::util::Class
sk::rt::json::BooleanItem::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::json::BooleanItem::
get() const
{
  if(isObtained() == false) {
    const Json::Value& value = getValue();
    try {
      _value = value.asBool();
    }
    catch(const std::exception& exception) {
      raiseArgumentException(exception);
    }
  }
  ensureAvailable();
  return _value;
}

void
sk::rt::json::BooleanItem::
set(const bool value)
{
  setValue(value);
}
