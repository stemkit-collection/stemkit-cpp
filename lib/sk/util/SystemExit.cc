/*  vim: set sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/SystemExit.h>

sk::util::SystemExit::
SystemExit(int code)
  : _code(code), _message("Unspecified")
{
}

sk::util::SystemExit::
SystemExit(int code, const std::string& message)
  : _code(code), _message(message)
{
}

sk::util::SystemExit::
SystemExit(const std::string& message)
  : _code(1), _message(message)
{
}

sk::util::SystemExit::
SystemExit(int code, const std::exception& exception)
  : _code(code), _message(exception.what())
{
}

sk::util::SystemExit::
SystemExit(const std::exception& exception)
  : _code(1), _message(exception.what())
{
}

int
sk::util::SystemExit::
getCode() const
{
  return _code;
}

const std::string
sk::util::SystemExit::
getMessage() const
{
  return _message;
}

