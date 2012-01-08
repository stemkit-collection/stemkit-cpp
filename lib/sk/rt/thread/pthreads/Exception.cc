/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "Exception.h"

static const char* __className("sk::rt::thread::pthreads::Exception");

sk::rt::thread::pthreads::Exception::
Exception(const sk::util::String& function, int code)
  : _function(function), sk::rt::SystemException(function, code)
{
}

sk::rt::thread::pthreads::Exception::
~Exception() throw()
{
}

const sk::util::Class
sk::rt::thread::pthreads::Exception::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::thread::pthreads::Exception::
raiseUnlessSuccess(const sk::util::String& statement, int status)
{
  if(status == 0) {
    return true;
  }
  throw Exception(statement.substring(0, statement.indexOf('(')).trim(), status);
}

bool
sk::rt::thread::pthreads::Exception::
raiseUnlessSuccess(const sk::util::String& statement, int status, const sk::util::Integers& others)
{
  if(status == 0) {
    return true;
  }
  if(others.contains(status)) {
    return false;
  }
  return raiseUnlessSuccess(statement, status);
}

const sk::util::String
sk::rt::thread::pthreads::Exception::
getFunctionName() const
{
  return _function;
}
