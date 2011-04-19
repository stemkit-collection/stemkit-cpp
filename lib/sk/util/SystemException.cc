/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/util/SystemException.h>
#include <errno.h>
#include <string.h>

namespace {
  const sk::util::String get_errno_message(int code) {
    const char* message = strerror(code);
    if(message != 0) {
      return message;
    }
    return "Error " + sk::util::String::valueOf(code);
  }
}

sk::util::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("System") << message << sk::util::String::valueOf(errno) << get_errno_message(errno)), _code(errno)
{
}

sk::util::SystemException::
SystemException(const sk::util::String& message, int code)
  : sk::util::Exception(sk::util::Strings("System") << message << sk::util::String::valueOf(code) << get_errno_message(code)), _code(code)
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
