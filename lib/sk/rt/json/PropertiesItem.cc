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
PropertiesItem()
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
