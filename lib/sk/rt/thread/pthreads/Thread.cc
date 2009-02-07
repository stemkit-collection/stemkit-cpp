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

sk::rt::thread::pthreads::Thread::
Thread(Runnable& target)
  : _target(target)
{
}

sk::rt::thread::pthreads::Thread::
~Thread()
{
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
    _target.run();
  }
  catch(const sk::util::SystemExit& exception) {
    pthread_exit(reinterpret_cast<void*>(exception.getCode()));
  }
  catch(...) {
    std::cerr << "!!! UNKNOWN THREAD EXCEPTION !!!" << std::endl;
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
