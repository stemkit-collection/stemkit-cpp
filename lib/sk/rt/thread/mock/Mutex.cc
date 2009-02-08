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

#include "Mutex.h"

static const sk::util::Class __class("sk::rt::thread::mock::Mutex");

sk::rt::thread::mock::Mutex::
Mutex()
  : _locked(false)
{
}

sk::rt::thread::mock::Mutex::
~Mutex()
{
}

const sk::util::Class
sk::rt::thread::mock::Mutex::
getClass() const
{
  return __class;
}

void
sk::rt::thread::mock::Mutex::
lock()
{
  _locked = true;
}

void
sk::rt::thread::mock::Mutex::
unlock()
{
  _locked = false;
}

bool
sk::rt::thread::mock::Mutex::
tryLock()
{
  _locked = true;
  return true;
}
