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
#include <sk/rt/SystemException.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Thread.h>
#include <sk/rt/ProcessInfo.h>

#include "Handler.h"

static const sk::util::String __className("test::Handler");

test::Handler::
Handler(int argc, const char* argv[])
  : _scope(__className)
{
}

test::Handler::
~Handler()
{
}

const sk::util::Class
test::Handler::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct Waiter : public virtual sk::rt::Runnable {
    Waiter(pid_t pid)
      : _scope("Waiter"), _pid(pid) {}

    void run() {
      int status = 0;
      int result = waitpid(_pid, &status, 0);

      _scope.info("R") << result;
      _scope.info("S") << std::hex << status;

      if(result == -1) {
        throw sk::rt::SystemException("waitpid");
      }
    }

    private: 
      sk::rt::Scope _scope;
      pid_t _pid;
  };

  struct Forker : public virtual sk::rt::Runnable {
    Forker() 
      : _scope("Forker") {}

    void run() {
      pid_t pid = fork();
      if(pid == 0) {
        sk::rt::ProcessInfo::reset();
        sleep(5);
        _scope.info("CHILD") << getpid();
        _exit(3);
      }
      if(pid < 0) {
        throw sk::rt::SystemException("fork");
      }
      _scope.info("PID") << pid;

      Waiter waiter(pid);
      sk::rt::Thread thread(waiter);

      thread.start();
      thread.join();
    }

    private:
      sk::rt::Scope _scope;
  };
}

void 
test::Handler::
start()
{
  Forker forker;
  sk::rt::Thread thread(forker);

  thread.start();
  thread.join();
}
