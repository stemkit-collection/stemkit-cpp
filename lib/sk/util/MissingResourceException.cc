/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/MissingResourceException.h>

sk::util::MissingResourceException::
MissingResourceException(const sk::util::String& message)
  : sk::util::Exception(join("Missing resource", message))
{
}

const sk::util::Class
sk::util::MissingResourceException::
getClass() const
{
  return sk::util::Class("sk::util::MissingResourceException");
}
