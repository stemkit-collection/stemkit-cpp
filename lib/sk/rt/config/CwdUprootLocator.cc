/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/config/CwdUprootLocator.h>
#include <unistd.h>

sk::rt::config::CwdUprootLocator::
CwdUprootLocator(const sk::util::String& item, const SpotLocator& other)
  : UprootLocator(item, figureCurrentDirectory(), other)
{
}

sk::rt::config::CwdUprootLocator::
CwdUprootLocator(const sk::util::String& item)
  : UprootLocator(item, figureCurrentDirectory())
{
}

sk::rt::config::CwdUprootLocator::
~CwdUprootLocator()
{
}

const sk::util::Class
sk::rt::config::CwdUprootLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::CwdUprootLocator");
}

const sk::util::String
sk::rt::config::CwdUprootLocator::
figureCurrentDirectory()
{
  char buffer[1024];
  return getcwd(buffer, sizeof(buffer));
}
