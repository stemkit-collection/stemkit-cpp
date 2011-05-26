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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/json/IntItem.h>

static const sk::util::String __className("sk::rt::json::IntItem");

sk::rt::json::IntItem::
IntItem(Json::Value& value, const sk::util::String& name)
  : sk::rt::json::Item(value, name)
{
}

sk::rt::json::IntItem::
~IntItem()
{
}

const sk::util::Class
sk::rt::json::IntItem::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::rt::json::IntItem::
get()
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
sk::rt::json::IntItem::
set(const int value)
{
  setValue(value);
}
