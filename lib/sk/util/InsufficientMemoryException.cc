/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>

#include <sk/util/InsufficientMemoryException.h>

sk::util::InsufficientMemoryException::
InsufficientMemoryException(const sk::util::String& purpose, int amount)
  : sk::util::Exception(join(join("Memory allocation", purpose), "amount=" + sk::util::Integer::toString(amount))),
    _amount(amount)
{
}

const sk::util::Class
sk::util::InsufficientMemoryException::
getClass() const
{
  return sk::util::Class("sk::util::InsufficientMemoryException");
}

int
sk::util::InsufficientMemoryException::
getRequestedAmount() const
{
  return _amount;
}
