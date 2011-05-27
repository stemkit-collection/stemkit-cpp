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

#include <sk/rt/json/PropertiesItem.h>

static const sk::util::String __className("sk::rt::json::PropertiesItem");

sk::rt::json::PropertiesItem::
PropertiesItem(Json::Value& value, const sk::util::String& name)
  : sk::rt::json::Item(value, name)
{
}

sk::rt::json::PropertiesItem::
~PropertiesItem()
{
}

const sk::util::Class
sk::rt::json::PropertiesItem::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::Properties&
sk::rt::json::PropertiesItem::
get()
{
  if(isObtained() == false) {
    const Json::Value& value = getValue();
    _value.clear();

    try {
      for(Json::Value::const_iterator iterator = value.begin(); iterator != value.end(); ++iterator) {
        _value.setProperty(iterator.key().asString(), (*iterator).asString());
      }
    }
    catch(const std::exception& exception) {
      raiseArgumentException(exception);
    }
  }
  ensureAvailable();
  return _value;
}

namespace {
  struct Propagator : public virtual sk::util::BinaryProcessor<const sk::util::String, const sk::util::String> {
    Propagator(Json::Value& properties)
      : _properties(properties) {}

    void process(const sk::util::String& key, const sk::util::String& value) const {
      _properties[key] = value;
    }

    Json::Value& _properties;
  };
}

void 
sk::rt::json::PropertiesItem::
set(const sk::util::Properties& value)
{
  Json::Value properties;
  value.forEach(Propagator(properties));

  setValue(properties);
}
