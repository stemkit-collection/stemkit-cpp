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
#include <windows.h>
#include <sstream>

static const char* __className("sk::rt::SystemException");

namespace {
  const sk::util::String getErrorString(uint32_t errorCode) {
	int flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    char* s;
	int n = FormatMessage(flags, 0, errorCode, 0, LPTSTR(&s), 0, 0);
 
    std::ostringstream stream;
	if(n == 0) {
      stream << "Error " << errorCode << "(no message found)";
    }
    else {
      stream << s;
      LocalFree(s);
    }
    return sk::util::String(stream.str()).trim();
  }
}

sk::rt::SystemException::
SystemException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("Runtime") << message << sk::util::String::valueOf(GetLastError()) << getErrorString(GetLastError())), _code(GetLastError())
{
}

sk::rt::SystemException::
SystemException(const sk::util::String& message, uint32_t code)
  : sk::util::Exception(sk::util::Strings("Runtime") << message << sk::util::String::valueOf(code) << getErrorString(code)), _code(code)
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
