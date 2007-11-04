/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/Locator.h>

sk::rt::config::Locator::
Locator()
{
}

sk::rt::config::Locator::
~Locator()
{
}

const sk::util::Class
sk::rt::config::Locator::
getClass() const
{
  return sk::util::Class("sk::rt::config::Locator");
}
