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
#include <string.h>

sk::util::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(join(join(join("System", message), errno), strerror(errno))), _code(errno)
{
}

sk::util::SystemException::
SystemException(const sk::util::String& message, int code)
  : sk::util::Exception(join(join(join("System", message), code), strerror(code))), _code(code)
{
}

const sk::util::Class
sk::util::SystemException::
getClass() const
{
  return sk::util::Class("sk::util::SystemException");
}

int
sk::util::SystemException::
getCode() const
{
  return _code;
}

bool
sk::util::SystemException::
raiseUnlessSuccess(const sk::util::String& statement, int status, int other)
{
  if(status < 0) {
    if(errno == other) {
      return false;
    }
    throw SystemException(statement.substring(0, statement.indexOf('(')).trim());
  }
  return true;
}
