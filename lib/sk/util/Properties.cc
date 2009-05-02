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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String 
sk::util::Properties::
getProperty(const sk::util::String& name, const sk::util::String& fallback) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String 
sk::util::Properties::
getProperty(const sk::util::String& name, const char* fallback) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::util::Properties::
getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::util::Properties::
getProperty(const sk::util::String& name, int fallback) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::util::Properties::
size() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::util::Properties::
hasProperty(const sk::util::String& name) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String 
sk::util::Properties::
dumpProperty(const sk::util::String& name) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const sk::util::String& value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const char* value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, const sk::util::Boolean& value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
setProperty(const sk::util::String& name, int value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
deleteProperty(const sk::util::String& name)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
  
void 
sk::util::Properties::
parseProperty(const sk::util::String& name)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
clear()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Properties::
forEach(const sk::util::BinaryProcessor<const sk::util::String, const sk::util::String>& processor) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
