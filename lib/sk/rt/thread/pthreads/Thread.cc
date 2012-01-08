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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/SystemExit.h>

#include "Thread.h"
#include "Exception.h"

#include <iostream>

static const char* __className("sk::rt::thread::pthreads::Thread");

namespace {
  struct DummyRunnable : public virtual sk::rt::Runnable {
    void run() {
    }
  } DUMMY_TARGET;
}

sk::rt::thread::pthreads::Thread::
Thread(const sk::rt::Scope& scope, const Provider& provider, sk::rt::thread::Generic& handle)
  : _scope(scope), _provider(provider), _handle(handle), _target(DUMMY_TARGET),
    _thread(pthread_self()), _wrapper(true), _stopping(false)
{
  _provider.installGeneric(_handle);
}

sk::rt::thread::pthreads::Thread::
Thread(const sk::rt::Scope& scope, const Provider& provider, sk::rt::Runnable& target, sk::rt::thread::Generic& handle)
  : _scope(scope), _provider(provider), _target(target), _handle(handle),
  _thread(0), _wrapper(false), _stopping(false)
{
}

sk::rt::thread::pthreads::Thread::
~Thread()
{
  if(_wrapper == true) {
    sk::util::Exception::guard(_scope.warning(), _provider, &Provider::clearGeneric, __FUNCTION__);
  }
}

const sk::util::Class
sk::rt::thread::pthreads::Thread::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::thread::pthreads::Thread::
start()
{
  if(_wrapper == true) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_create(&_thread, 0, runner, this));
}

void
sk::rt::thread::pthreads::Thread::
stop()
{
  _stopping = true;
  try {
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cancel(_thread));
  }
  catch(...) {
    _stopping = false;
    throw;
  }
}

void
sk::rt::thread::pthreads::Thread::
interrupt()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::rt::thread::pthreads::Thread::
join()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_join(_thread, 0));
}

void
sk::rt::thread::pthreads::Thread::
detach()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_detach(_thread));
}

void
sk::rt::thread::pthreads::Thread::
run()
{
  try {
    _provider.installGeneric(_handle);
    _target.run();
    _stopping = false;
  }
  catch(const sk::util::SystemExit& exception) {
    pthread_exit(reinterpret_cast<void*>(exception.getCode()));
  }
  catch(const std::exception& exception) {
    _scope.warning() << exception.what();
    pthread_exit(reinterpret_cast<void*>(-1));
  }
  catch(...) {
    if(_stopping == true) {
      _stopping = false;
      throw;
    }
    _scope.warning() << "Unknown exception";
    pthread_exit(reinterpret_cast<void*>(-1));
  }
}

void*
sk::rt::thread::pthreads::Thread::
runner(void* data)
{
  static_cast<Thread*>(data)->run();
  return 0;
}
