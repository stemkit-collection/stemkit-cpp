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
#include <sk/util/MissingResourceException.h>
#include <sk/util/IllegalArgumentException.h>

#include <sk/rt/json/Item.h>

static const sk::util::String __className("sk::rt::json::Item");

sk::rt::json::Item::
Item(Json::Value& params, const sk::util::String& name)
  : _params(params), _name(name), _obtained(false), _available(false)
{
}

sk::rt::json::Item::
~Item()
{
}

const sk::util::Class
sk::rt::json::Item::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String&
sk::rt::json::Item::
name() const
{
  return _name;
}

bool
sk::rt::json::Item::
isObtained() const 
{
  return _obtained;
}

const Json::Value&
sk::rt::json::Item::
getValue() const
{
  const Json::Value& value = _params[_name];
  _obtained = true;

  if(value.isNull() == true) {
    ensureAvailable();
  }
  _available = true;
  return value;
}

void
sk::rt::json::Item::
setValue(const Json::Value& value)
{
  _params[_name] = value;
  _obtained = false;
  _available = true;
}

void
sk::rt::json::Item::
ensureAvailable() const
{
  if(_available == false) {
    throw sk::util::MissingResourceException(getClass().getName(), _name);
  }
}

bool
sk::rt::json::Item::
isPresent() const
{
  if(_obtained == false && _available == false) {
    _available = (_params[_name].isNull() == false ? true : false);
  }
  return _available;

}

void 
sk::rt::json::Item::
raiseArgumentException(const std::exception& exception) const
{
  throw sk::util::IllegalArgumentException(getClass().getName(), sk::util::Strings(_name) << exception.what());
}
