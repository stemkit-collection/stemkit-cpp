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

#include <sk/rt/json/IntegerItem.h>

static const sk::util::String __className("sk::rt::json::IntegerItem");

sk::rt::json::IntegerItem::
IntegerItem(Json::Value& value, const sk::util::String& name)
  : sk::rt::json::Item(value, name)
{
}

sk::rt::json::IntegerItem::
~IntegerItem()
{
}

const sk::util::Class
sk::rt::json::IntegerItem::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::rt::json::IntegerItem::
get() const
{
  if(isObtained() == false) {
    const Json::Value& value = getValue();
    try {
      _value = value.asInt();
    }
    catch(const std::exception& exception) {
      raiseArgumentException(exception);
    }
  }
  ensureAvailable();
  return _value;
}

void
sk::rt::json::IntegerItem::
set(const int value)
{
  setValue(value);
}
