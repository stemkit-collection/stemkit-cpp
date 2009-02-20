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

static const sk::util::Class __class("sk::rt::thread::pthreads::Exception");

sk::rt::thread::pthreads::Exception::
Exception(const sk::util::String& name, int code)
  : SystemException(name, code)
{
}

const sk::util::Class
sk::rt::thread::pthreads::Exception::
getClass() const
{
  return __class;
}

bool
sk::rt::thread::pthreads::Exception::
raiseUnlessSuccess(const sk::util::String& name, int status, int other)
{
  if(status != 0) {
    if(status == other) {
      return false;
    }
    throw Exception(name, status);
  }
  return true;
}

