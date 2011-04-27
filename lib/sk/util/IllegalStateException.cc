/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/util/IllegalStateException.h>

sk::util::IllegalStateException::
IllegalStateException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("Illegal state") << message)
{
}

sk::util::IllegalStateException::
IllegalStateException(const sk::util::String& message, const sk::util::Strings& details)
  : sk::util::Exception(sk::util::Strings("Illegal state") << message << details)
{
}

const sk::util::Class
sk::util::IllegalStateException::
getClass() const
{
  return sk::util::Class("sk::util::IllegalStateException");
}
