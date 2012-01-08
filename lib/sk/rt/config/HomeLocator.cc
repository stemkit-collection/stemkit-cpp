/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/HomeLocator.h>
#include <stdlib.h>

sk::rt::config::HomeLocator::
HomeLocator(const sk::util::String& item, const SpotLocator& other)
  : SpotLocator(item, figureHomeLocation(), other)
{
}

sk::rt::config::HomeLocator::
HomeLocator(const sk::util::String& item)
  : SpotLocator(item, figureHomeLocation())
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

const sk::util::String
sk::rt::config::HomeLocator::
figureHomeLocation()
{
  return getenv("HOME");
}
