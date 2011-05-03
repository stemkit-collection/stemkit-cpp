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
#include <sk/util/Strings.h>

#include <sk/rt/SystemException.h>
#include <errno.h>
#include <string.h>

static const char* __className("sk::rt::SystemException");

namespace {
  const sk::util::String get_errno_message(int code) {
    const char* message = strerror(code);
    if(message == 0) {
      message = "Unknown system error";
    }
    return sk::util::String(message) + " (" + sk::util::String::valueOf(code) + ")";
  }
}

sk::rt::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("Runtime") << message << get_errno_message(errno)), _code(errno)
{
}

sk::rt::SystemException::
SystemException(const sk::util::String& message, uint32_t code)
  : sk::util::Exception(sk::util::Strings("Runtime") << message << get_errno_message(code)), _code(code)
{
}

sk::rt::SystemException::
SystemException(const sk::util::String& message, const sk::util::Strings& details)
  : sk::util::Exception(sk::util::Strings("Runtime") << message << get_errno_message(errno) << details), _code(errno)
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
