/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/NumberFormatException.h>

sk::util::NumberFormatException::
NumberFormatException(const sk::util::String& message)
  : sk::util::Exception(join("Wrong number format", message))
{
}

const sk::util::Class
sk::util::NumberFormatException::
getClass() const
{
  return sk::util::Class("sk::util::NumberFormatException");
}
