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
#include <sk/rt/Mutex.h>
#include <sk/rt/Locker.h>
#include <sk/rt/ProcessInfo.h>
#include <sk/util/ArrayList.cxx>

#include "Handler.h"
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static const sk::util::String __className("test::Handler");

test::Handler::
Handler(int argc, const char* const argv[])
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
    Waiter()
      : _scope("Waiter") {}

    void run() {
      _scope.info("PIDS") << _pids.join(", ");
      while(true) {
        int status = 0;
        int result = waitpid(-1, &status, 0);

        _scope.info("waitpid") << "R: " << result << ", S: " << std::hex << status;

        if(result == -1) {
          if(errno == ECHILD) {
            _scope.info("No more children.");
            break;
          }
          throw sk::rt::SystemException("waitpid");
        }
        if(_pids.contains(result) == false) {
          throw sk::util::IllegalStateException("PID MISMATCH!!!");
        }
      }
    }

    void add(pid_t pid) {
      _pids.add(pid);
      _scope.info() << "Pid " << pid << " added (" << _pids.join(", ") << ")";
    }

    private:
      sk::rt::Scope _scope;
      sk::util::ArrayList<pid_t>::Copying _pids;
  };

  struct Forker : public virtual sk::rt::Runnable {
    Forker(sk::rt::Lock& lock, Waiter& waiter)
      : _scope("Forker"), _lock(lock), _waiter(waiter) {}

    void run() {
      // sk::rt::Locker locker(_lock);

      pid_t pid = fork();
      if(pid == 0) {
        sk::rt::ProcessInfo::reset();
        sleep(10);
        _exit(3);
      }
      if(pid < 0) {
        throw sk::rt::SystemException("fork");
      }
      _scope.info("PID") << pid;
      _waiter.add(pid);
    }

    private:
      sk::rt::Scope _scope;
      sk::rt::Lock& _lock;
      Waiter& _waiter;
  };

  struct Starter : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.start();
      sk::rt::Thread::sleep(100);
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
  sk::rt::Scope scope("start");
  sk::util::ArrayList<sk::rt::Thread> threads;
  sk::rt::Mutex mutex;
  Waiter waiter;

  for(int counter=50; counter ;--counter) {
    threads.add(new sk::rt::Thread(new Forker(mutex, waiter)));
  }
  scope.info() << "Threads created";

  threads.forEach(Starter());
  scope.info() << "Threads started";

  threads.forEach(Joiner());
  scope.info() << "Threads done";

  sk::rt::Thread waiterThread(waiter);
  scope.info() << "Waiter thread created";

  waiterThread.start();
  scope.info() << "Waiter thread started";

  waiterThread.join();
  scope.info() << "Waiter thread done";
}
