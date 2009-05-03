/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalArgumentException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/NumberFormatException.h>
#include <sk/util/Integer.h>
#include <sk/util/StringArray.h>

#include <sk/util/Properties.h>

static const char* __className("sk::util::Properties");

sk::util::Properties::
Properties()
{
}

sk::util::Properties::
~Properties()
{
}

const sk::util::Class
sk::util::Properties::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String 
sk::util::Properties::
getProperty(const sk::util::String& name) const
{
  container::const_iterator iterator = _depot.find(name);
  if(iterator != _depot.end()) {
    return iterator->second;
  }
  throw sk::util::NoSuchElementException(name);
}

const sk::util::String 
sk::util::Properties::
getProperty(const sk::util::String& name, const sk::util::String& fallback) const
{
  container::const_iterator iterator = _depot.find(name);
  if(iterator != _depot.end()) {
    return (*iterator).second;
  }
  return fallback;
}

const sk::util::String 
sk::util::Properties::
getProperty(const sk::util::String& name, const char* fallback) const
{
  return getProperty(name, sk::util::String(fallback));
}

bool 
sk::util::Properties::
getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const
{
  container::const_iterator iterator = _depot.find(name);
  if(iterator != _depot.end()) {
    return sk::util::Boolean::parseBoolean(iterator->second);
  }
  return fallback.booleanValue();
}

int 
sk::util::Properties::
getProperty(const sk::util::String& name, int fallback) const
{
  container::const_iterator iterator = _depot.find(name);
  if(iterator != _depot.end()) {
    try {
      return sk::util::Integer::parseInt(iterator->second);
    }
    catch(const sk::util::NumberFormatException& exception) {}
  }
  return fallback;
}

int 
sk::util::Properties::
size() const
{
  return _depot.size();
}

bool 
sk::util::Properties::
hasProperty(const sk::util::String& name) const
{
  return _depot.find(name) != _depot.end();
}

const sk::util::String 
sk::util::Properties::
dumpProperty(const sk::util::String& name) const
{
  return name + "=" + getProperty(name);
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const sk::util::String& value)
{
  _depot[name] = value;
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const char* value)
{
  setProperty(name, sk::util::String(value));
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const sk::util::Boolean& value)
{
  setProperty(name, value.toString());
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, int value)
{
  setProperty(name, sk::util::String::valueOf(value));
}

bool 
sk::util::Properties::
deleteProperty(const sk::util::String& name)
{
  return _depot.erase(name) == 0 ? false : true;
}
  
void 
sk::util::Properties::
parseProperty(const sk::util::String& specification)
{
  int separator = specification.indexOf('=');
  if(separator > 0) {
    sk::util::String name = specification.substring(0, separator).trim();
    if(name.isEmpty() == false) {
      setProperty(name, specification.substring(separator + 1));
      return;
    }
  }
  throw sk::util::IllegalArgumentException(specification.inspect());
}

void 
sk::util::Properties::
clear()
{
  _depot.clear();
}

void 
sk::util::Properties::
forEach(const sk::util::BinaryProcessor<const sk::util::String, const sk::util::String>& processor) const
{
  for(container::const_iterator iterator=_depot.begin(); iterator != _depot.end() ;++iterator) {
    processor.process(iterator->first, iterator->second);
  }
}

const sk::util::String
sk::util::Properties::
inspect() const
{
  sk::util::StringArray result;
  for(container::const_iterator iterator=_depot.begin(); iterator != _depot.end() ;++iterator) {
    result << (iterator->first + " => " + iterator->second.inspect());
  }
  if(result.isEmpty() == true) {
    return "{}";
  }
  return "{ " + result.join(", ") + " }";
}
