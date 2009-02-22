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

#include "CriticalSection.h"

static const sk::util::Class __class("sk::rt::thread::win32::CriticalSection");

sk::rt::thread::win32::CriticalSection::
CriticalSection()
  : _scope(__class.getName())
{
  InitializeCriticalSection(&_section);
}

sk::rt::thread::win32::CriticalSection::
~CriticalSection()
{
  sk::util::Exception::guard(_scope.warning(__FUNCTION__), *this, &CriticalSection::cleanup);
}

void 
sk::rt::thread::win32::CriticalSection::
cleanup()
{
  DeleteCriticalSection(&_section);
}

const sk::util::Class
sk::rt::thread::win32::CriticalSection::
getClass() const
{
  return __class;
}

void 
sk::rt::thread::win32::CriticalSection::
lock()
{
  EnterCriticalSection(&_section);
}

void 
sk::rt::thread::win32::CriticalSection::
unlock()
{
  LeaveCriticalSection(&_section);
}

bool 
sk::rt::thread::win32::CriticalSection::
tryLock()
{
  return TryEnterCriticalSection(&_section);
}

bool 
sk::rt::thread::win32::CriticalSection::
hasEnterCount() const
{
  return true;
}

int 
sk::rt::thread::win32::CriticalSection::
getEnterCount() const
{
  return _section.RecursionCount;
}

