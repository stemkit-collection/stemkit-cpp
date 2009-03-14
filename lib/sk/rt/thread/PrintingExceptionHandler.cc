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
#include <sk/util/Boolean.h>
#include <sk/rt/thread/Generic.h>

#include "PrintingExceptionHandler.h"
#include <unistd.h>

static const char* __className("sk::rt::thread::PrintingExceptionHandler");

sk::rt::thread::PrintingExceptionHandler::
PrintingExceptionHandler(const sk::util::String& name)
  : _scope(name)
{
  _abortOnException = _scope.getProperty("abort-on-exception", sk::util::Boolean::B_FALSE);
}

sk::rt::thread::PrintingExceptionHandler::
~PrintingExceptionHandler()
{
}

const sk::util::Class
sk::rt::thread::PrintingExceptionHandler::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::thread::PrintingExceptionHandler::
uncaughtException(sk::rt::thread::Generic& thread, const std::exception& exception)
{
  _scope.warning() << thread.inspect() << ": " << exception.what();
  finalize();
}

void 
sk::rt::thread::PrintingExceptionHandler::
uncaughtException(sk::rt::thread::Generic& thread)
{
  _scope.warning() << thread.inspect() << ": " << "Unknown error";
  finalize();
}

void
sk::rt::thread::PrintingExceptionHandler::
finalize()
{
  if(_abortOnException == true) {
    _exit(2);
  }
}
