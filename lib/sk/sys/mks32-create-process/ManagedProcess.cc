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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/rt/SystemException.h>

#include "ManagedProcess.h"
#include <winnutc.h>

static const char* __className("sk::sys::ManagedProcess");

sk::sys::ManagedProcess::
ManagedProcess(int pid)
  : _pid(pid)
{
  _handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if(_handle == 0) {
    throw sk::rt::SystemException("OpenProcess");
  }
}

sk::sys::ManagedProcess::
~ManagedProcess()
{
  CloseHandle(_handle);
}

const sk::util::Class
sk::sys::ManagedProcess::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::sys::ManagedProcess::
getPid() const
{
  return _pid;
}

void
sk::sys::ManagedProcess::
stop()
{
  if(terminate(3) == false) {
    kill();
  }
}

void
sk::sys::ManagedProcess::
kill()
{
  if(terminate(0) == false) {
    // throw sk::util::IllegalStateException("Cannot stop process:" + sk::util::String::valueOf(_pid));
  }
}

bool
sk::sys::ManagedProcess::
terminate(int tolerance)
{
  if(tolerance == 0) {
    if(TerminateProcess(_handle, 43195) == FALSE) {
      throw sk::rt::SystemException("TerminateProcess");
    }
    Sleep(1000);
  }
  return isAlive() == false;
}

void
sk::sys::ManagedProcess::
join()
{
  if(WaitForSingleObject(_handle, INFINITE) == WAIT_FAILED) {
    throw sk::rt::SystemException("WaitForSingleObject");
  }
}

void
sk::sys::ManagedProcess::
detach()
{
}

bool
sk::sys::ManagedProcess::
isSuccess() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::ManagedProcess::
isExited() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::ManagedProcess::
isKilled() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::ManagedProcess::
isAlive() const
{
  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _pid);
  if(handle == 0) {
    return false;
  }
  CloseHandle(handle);
  return true;
}

int
sk::sys::ManagedProcess::
exitStatus() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int
sk::sys::ManagedProcess::
signal() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
