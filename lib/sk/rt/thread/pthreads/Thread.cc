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
#include <sk/util/SystemException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/SystemExit.h>

#include "Thread.h"
#include <iostream>

static const sk::util::Class __class("sk::rt::thread::pthreads::Thread");

namespace {
  void exceptionUnlessSuccess(const char* name, int status) {
    if(status != 0) {
      throw sk::util::SystemException("pthread_" + sk::util::String(name) + "()", status);
    }
  }
}

namespace {
  struct DummyRunnable : public virtual sk::rt::Runnable {
    void run() const {
    }
  } DUMMY_TARGET;
}

sk::rt::thread::pthreads::Thread::
Thread(const Provider& provider, sk::rt::thread::Generic& handle)
  : _scope(__class.getName()), _provider(provider), _handle(handle), _target(DUMMY_TARGET), _thread(pthread_self()), _wrapper(true)
{
  _provider.installGeneric(_handle);
}

sk::rt::thread::pthreads::Thread::
Thread(const Provider& provider, sk::rt::Runnable& target, sk::rt::thread::Generic& handle)
  : _scope(__class.getName()), _provider(provider), _target(target), _handle(handle), _wrapper(false)
{
}

sk::rt::thread::pthreads::Thread::
~Thread()
{
  if(_wrapper == true) {
    try {
      _provider.clearGeneric();
    }
    catch(...) {}
  }
}

const sk::util::Class
sk::rt::thread::pthreads::Thread::
getClass() const
{
  return __class;
}

void 
sk::rt::thread::pthreads::Thread::
start()
{
  if(_wrapper == true) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  exceptionUnlessSuccess("create", pthread_create(&_thread, 0, runner, this));
}

void 
sk::rt::thread::pthreads::Thread::
stop()
{
  exceptionUnlessSuccess("cancel", pthread_cancel(_thread));
}

void 
sk::rt::thread::pthreads::Thread::
interrupt()
{
  exceptionUnlessSuccess("cancel", pthread_cancel(_thread));
}

void 
sk::rt::thread::pthreads::Thread::
join()
{
  exceptionUnlessSuccess("join", pthread_join(_thread, 0));
}

void 
sk::rt::thread::pthreads::Thread::
run()
{
  try {
    _provider.installGeneric(_handle);
    _target.run();
  }
  catch(const sk::util::SystemExit& exception) {
    pthread_exit(reinterpret_cast<void*>(exception.getCode()));
  }
  catch(const std::exception& exception) {
    _scope.warning() << exception.what();
    pthread_exit(reinterpret_cast<void*>(-1));
  }
  catch(...) {
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
