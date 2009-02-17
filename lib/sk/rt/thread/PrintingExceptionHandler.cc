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
#include <sk/util/UnsupportedOperationException.h>

#include "PrintingExceptionHandler.h"

static const sk::util::Class __class("sk::rt::thread::PrintingExceptionHandler");

sk::rt::thread::PrintingExceptionHandler::
PrintingExceptionHandler()
{
}

sk::rt::thread::PrintingExceptionHandler::
~PrintingExceptionHandler()
{
}

const sk::util::Class
sk::rt::thread::PrintingExceptionHandler::
getClass() const
{
  return __class;
}

void 
sk::rt::thread::PrintingExceptionHandler::
uncaughtException(sk::rt::thread::Generic& thread, const std::exception& exception)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::thread::PrintingExceptionHandler::
uncaughtException(sk::rt::thread::Generic& thread)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
