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
#include <sk/util/IllegalStateException.h>

#include "CriticalSection.h"

static const char* __className("sk::rt::thread::win32::CriticalSection");

sk::rt::thread::win32::CriticalSection::
CriticalSection()
  : _scope(__className), _depth(0), _errorCheck(true)
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
  return sk::util::Class(__className);
}

void 
sk::rt::thread::win32::CriticalSection::
lock()
{
  EnterCriticalSection(&_section);
  ensureDepth(true);
}

bool
sk::rt::thread::win32::CriticalSection::
ensureDepth(bool raise)
{
  if(_depth > 0) {
    if(getEnterCount() > _depth) {
      LeaveCriticalSection(&_section);
      if(raise == true) {
        throw sk::util::IllegalStateException("lock: too deep");
      }
      return false;
    }
  }
  return true;
}

void 
sk::rt::thread::win32::CriticalSection::
unlock()
{
  if(_errorCheck == true) {
    if(TryEnterCriticalSection(&_section) == TRUE) {
      int count = getEnterCount();
      LeaveCriticalSection(&_section);
      if(count == 1) {
        throw sk::util::IllegalStateException("unlock: not locked");
      }
    }
    else {
      throw sk::util::IllegalStateException("unlock: not owner");
    }
  }
  LeaveCriticalSection(&_section);
}

bool 
sk::rt::thread::win32::CriticalSection::
tryLock()
{
  if(TryEnterCriticalSection(&_section) == TRUE) {
    return ensureDepth(false);
  }
  return false;
}

void 
sk::rt::thread::win32::CriticalSection::
reset()
{
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

void
sk::rt::thread::win32::CriticalSection::
setDepth(int depth) 
{
  _depth = depth<0 ? 0 : depth;
}

void
sk::rt::thread::win32::CriticalSection::
setErrorCheck(bool state)
{
  _errorCheck = state;
}
