/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/SystemException.h>
#include <errno.h>

static const char* __className("sk::rt::SystemException");

namespace {
  const sk::util::String get_errno_message(int code) {
    char buffer[1024];
    if(strerror_r(code, buffer, sizeof(buffer)) == 0) {
      return buffer;
    }
    return "Error " + sk::util::String::valueOf(code);
  }
}

sk::rt::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(join(join(join("Runtime", message), errno), get_errno_message(errno))), _code(errno)
{
}

sk::rt::SystemException::
SystemException(const sk::util::String& message, uint32_t code)
  : sk::util::Exception(join(join(join("Runtime", message), code), get_errno_message(code))), _code(code)
{
}

const sk::util::Class
sk::rt::SystemException::
getClass() const
{
  return sk::util::Class(__className);
}

uint32_t
sk::rt::SystemException::
getCode() const
{
  return _code;
}

bool
sk::rt::SystemException::
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
