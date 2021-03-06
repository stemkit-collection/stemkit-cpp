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
#include <sk/util/SystemExit.h>
#include <sk/rt/SystemException.h>

#include "Thread.h"

static const char* __className("sk::rt::thread::win32::Thread");

namespace {
  struct DummyRunnable : public virtual sk::rt::Runnable {
    void run() {
    }
  } DUMMY_TARGET;
}

sk::rt::thread::win32::Thread::
Thread(const Provider& provider, sk::rt::thread::Generic& handle)
  : _scope(__className), _provider(provider), _handle(handle), _target(DUMMY_TARGET), 
  _threadHandle(GetCurrentThread()), _threadId(GetCurrentThreadId()), _wrapper(true)
{
  _provider.installGeneric(_handle);
}

sk::rt::thread::win32::Thread::
Thread(const Provider& provider, sk::rt::Runnable& target, sk::rt::thread::Generic& handle)
  : _scope(__className), _provider(provider), _target(target), _handle(handle), 
  _threadHandle(0), _threadId(0), _wrapper(false)
{
}

sk::rt::thread::win32::Thread::
~Thread()
{
  if(_wrapper == true) {
    sk::util::Exception::guard(_scope.warning(__FUNCTION__), _provider, &Provider::clearGeneric);
  }
  sk::util::Exception::guard(_scope.warning(__FUNCTION__), *this, &Thread::cleanup);
}

void 
sk::rt::thread::win32::Thread::
cleanup()
{
  if(_threadHandle != 0) {
    if(CloseHandle(_threadHandle) == 0) {
      // No action here as the handle will always be invalid after the actual
      // thread is terminated.
      //
      // throw sk::rt::SystemException("Cannot close thread handle");
    }
  }
}

const sk::util::Class
sk::rt::thread::win32::Thread::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::thread::win32::Thread::
start()
{
  if(_wrapper == true) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  _threadHandle = CreateThread(0, 0, runner, this, 0, &_threadId);
  if(_threadHandle == 0) {
    throw sk::util::IllegalStateException("Cannot create thread");
  }
}

void 
sk::rt::thread::win32::Thread::
stop()
{
  if(TerminateThread(_threadHandle, -1) == FALSE) {
    throw sk::util::IllegalStateException("Cannot terminate thread");
  }
}

void 
sk::rt::thread::win32::Thread::
interrupt()
{
  stop();
}

void 
sk::rt::thread::win32::Thread::
join()
{
  if(WaitForSingleObject(_threadHandle, INFINITE) == WAIT_FAILED) {
    throw sk::util::IllegalStateException("Cannot join thread");
  }
}

void 
sk::rt::thread::win32::Thread::
detach()
{
}

void 
sk::rt::thread::win32::Thread::
run()
{
  try {
    _provider.installGeneric(_handle);
    _target.run();
  }
  catch(const sk::util::SystemExit& exception) {
    ExitThread(exception.getCode());
  }
  catch(const std::exception& exception) {
    _scope.warning() << exception.what();
    ExitThread(-1);
  }
  catch(...) {
    _scope.warning() << "Unknown exception";
    ExitThread(-1);
  }
}

DWORD
sk::rt::thread::win32::Thread::
runner(LPVOID data)
{
  static_cast<Thread*>(data)->run();
  return 0;
}
