/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/HomeLocator.h>

sk::rt::config::HomeLocator::
HomeLocator()
{
}

sk::rt::config::HomeLocator::
~HomeLocator()
{
}

const sk::util::Class
sk::rt::config::HomeLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::HomeLocator");
}
