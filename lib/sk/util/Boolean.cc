/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>

#include <strings.h>

const sk::util::Boolean sk::util::Boolean::B_TRUE(true);
const sk::util::Boolean sk::util::Boolean::B_FALSE(false);

sk::util::Boolean::
Boolean(bool value)
  : _value(value)
{
}

sk::util::Boolean::
Boolean(const sk::util::String& value)
  : _value(parseBoolean(value))
{
}

sk::util::Boolean::
~Boolean()
{
}

const sk::util::Class
sk::util::Boolean::
getClass() const
{
  return sk::util::Class("sk::util::Boolean");
}

bool
sk::util::Boolean::
booleanValue() const
{
  return _value;
}

bool
sk::util::Boolean::
parseBoolean(const sk::util::String& value)
{
  const char* true_values[] = {
    "true", "yes", "on", "t"
  };
  for(int index=0; index < sizeof(true_values)/sizeof(*true_values) ;index++) {
    if(strcasecmp(true_values[index], value.getChars()) == 0) {
      return true;
    }
  }
  return false;
}

const sk::util::Boolean&
sk::util::Boolean::
valueOf(bool value)
{
  return value ? B_TRUE : B_FALSE;
}

#include <iostream>

const sk::util::Boolean&
sk::util::Boolean::
valueOf(const sk::util::String& value)
{
  return valueOf(parseBoolean(value));
}

const sk::util::Boolean&
sk::util::Boolean::
valueOf(const char* value)
{
  return valueOf(sk::util::String(value));
}

const sk::util::String
sk::util::Boolean::
toString() const
{
  return _value ? "true" : "false";
}

const sk::util::String
sk::util::Boolean::
toString(bool value) 
{
  return valueOf(value).toString();
}
