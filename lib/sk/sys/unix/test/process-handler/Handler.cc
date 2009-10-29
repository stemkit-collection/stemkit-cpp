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
#include <sk/util/IllegalStateException.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Thread.h>
#include <sk/rt/ProcessInfo.h>
#include <sk/util/ArrayList.cxx>

#include "Handler.h"
#include <sys/wait.h>

static const sk::util::String __className("test::Handler");

test::Handler::
Handler(int /*argc*/, const char* /*argv*/[])
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

      _scope.info("waitpid") << "R: " << result << ", P: " << _pid << ", S: " << std::hex << status;

      if(result == -1) {
        throw sk::rt::SystemException("waitpid");
      }
      if(result != _pid) {
        throw sk::util::IllegalStateException("PID MISMATCH!!!");
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
        sleep(2);
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

      _scope.info() << "DONE";
    }

    private:
      sk::rt::Scope _scope;
  };

  struct Starter : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.start();
    }
  };

  struct Joiner : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.join();
    }
  };
}

void 
test::Handler::
start()
{
  sk::util::ArrayList<sk::rt::Thread> threads;

  for(int counter=10; counter ;--counter) {
    threads.add(new sk::rt::Thread(new Forker));
  }
  threads.forEach(Starter());
  threads.forEach(Joiner());
}
