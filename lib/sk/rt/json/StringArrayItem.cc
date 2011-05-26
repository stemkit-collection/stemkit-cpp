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

#include <sk/rt/json/StringArrayItem.h>

static const sk::util::String __className("sk::rt::json::StringArrayItem");

sk::rt::json::StringArrayItem::
StringArrayItem(const Json::Value& value, const sk::util::String& name)
  : sk::rt::json::Item(value, name)
{
}

sk::rt::json::StringArrayItem::
~StringArrayItem()
{
}

const sk::util::Class
sk::rt::json::StringArrayItem::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::Strings&
sk::rt::json::StringArrayItem::
get()
{
  if(isObtained() == false) {
    const Json::Value& value = getValue();
    try {
      int size = value.size();
      for(int index=0; index < size; ++index) {
        _value << value[index].asString();
      }
    }
    catch(const std::exception& exception) {
      raiseArgumentException(exception);
    }
  }
  ensureAvailable();
  return _value;
}
