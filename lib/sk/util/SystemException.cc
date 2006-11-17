/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/SystemException.h>
#include <errno.h>

sk::util::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(join(join(join("System", message), errno), strerror(errno)))
{
}

const sk::util::Class
sk::util::SystemException::
getClass() const
{
  return sk::util::Class("sk::util::SystemException");
}
