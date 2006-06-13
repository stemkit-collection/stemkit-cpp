/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/NoSuchElementException.h>

sk::util::NoSuchElementException::
NoSuchElementException(const sk::util::String& message)
  : sk::util::Exception(join("No such element", message))
{
}

const sk::util::Class
sk::util::NoSuchElementException::
getClass() const
{
  return sk::util::Class("sk::util::NoSuchElementException");
}
