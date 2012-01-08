/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <sk/util/Integer.h>

#include <sk/util/InsufficientMemoryException.h>

sk::util::InsufficientMemoryException::
InsufficientMemoryException(const sk::util::String& purpose, size_t amount)
  : sk::util::Exception(sk::util::Strings("Memory allocation") << purpose << sk::util::Integer::toString(amount)),
    _amount(amount)
{
}

const sk::util::Class
sk::util::InsufficientMemoryException::
getClass() const
{
  return sk::util::Class("sk::util::InsufficientMemoryException");
}

size_t
sk::util::InsufficientMemoryException::
getRequestedAmount() const
{
  return _amount;
}
