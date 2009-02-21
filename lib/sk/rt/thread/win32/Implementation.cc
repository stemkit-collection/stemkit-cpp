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

#include "Implementation.h"

static const sk::util::Class __class("sk::rt::thread::win32::Implementation");

sk::rt::thread::win32::Implementation::
Implementation()
  : _scope(__class.getName())
{
  _tlsIndex = TlsAlloc();
  if(_tlsIndex == TLS_OUT_OF_INDEXES) {
    throw sk::util::IllegalStateException("No TLS indexes");
  }
}

sk::rt::thread::win32::Implementation::
~Implementation()
{
  sk::util::Exception::guard(_scope.warning(__FUNCTION__), *this, &Implementation::cleanup);
}

void
sk::rt::thread::win32::Implementation::
cleanup()
{
  if(TlsFree(_tlsIndex) != TRUE) {
    throw sk::util::IllegalStateException("TLS release failure");
  }
}

const sk::util::Class
sk::rt::thread::win32::Implementation::
getClass() const
{
  return __class;
}

sk::rt::thread::abstract::Mutex* 
sk::rt::thread::win32::Implementation::
makeSimpleMutex() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Mutex* 
sk::rt::thread::win32::Implementation::
makeRecursiveMutex() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Thread* 
sk::rt::thread::win32::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::thread::abstract::Thread* 
sk::rt::thread::win32::Implementation::
wrapCurrentThread(sk::rt::thread::Generic& handle) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::rt::thread::win32::Implementation::
installGeneric(sk::rt::thread::Generic& handle) const
{
  LPVOID value = TlsGetValue(_tlsIndex);
  if(value != 0) {
    throw sk::util::IllegalStateException("Generic is already initialized for this thread");
  }
  if(TlsSetValue(_tlsIndex, &handle) != TRUE) {
    throw sk::util::IllegalStateException("Generic setup failure");
  }
}

void
sk::rt::thread::win32::Implementation::
clearGeneric() const
{
  if(TlsSetValue(_tlsIndex, 0) != TRUE) {
    throw sk::util::IllegalStateException("Generic reset failure");
  }
}

sk::rt::thread::Generic& 
sk::rt::thread::win32::Implementation::
getGeneric() const
{
  LPVOID value = TlsGetValue(_tlsIndex);
  if(value == 0) {
    throw sk::util::IllegalStateException("Generic not initialized for this thread");
  }
  return *static_cast<sk::rt::thread::Generic*>(value);
}

void 
sk::rt::thread::win32::Implementation::
sleep(uint64_t milliseconds) const
{
  Sleep(milliseconds);
}

void
sk::rt::thread::win32::Implementation::
yield() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
