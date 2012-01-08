/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/Thread.h>
#include <sk/rt/thread/Starter.h>
#include <sk/rt/thread/Stopper.h>
#include <sk/rt/thread/Joiner.h>
#include <sk/rt/ReentrantLock.h>
#include <sk/rt/Locker.h>

#include <sk/util/ArrayList.cxx>

#include <unistd.h>
#include <iostream>

void perform();

int main(int /*argc*/, const char* /*argv*/[])
{
  sk::rt::Thread::setup();

  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <scope name='sk::rt::thread::pthread::Mutex'>\n\
          <log destination='std::cerr' level='error' show-object='false' show-time='true' />\n\
        </scope>\n\
        <scope name='sk::rt::thread::pthread::Thread'>\n\
          <log destination='std::cerr' level='error' show-object='false' show-time='true' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );

  perform();

  sk::rt::Thread::reset();
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block(const sk::util::String& message, sk::rt::Lock& lock)
      : _message(message), _lock(lock) {}

    void run() {
      while(true) {
        (sk::rt::Locker(_lock), tick());
        sk::rt::Thread::sleep(1000);
      }
    }

    void tick() const {
      sk::rt::thread::Generic& current = sk::rt::Thread::currentThread();
      std::cerr << "TICK: "
        << current.inspect() << ": "
        << _message.inspect() << ", " << _lock.inspect()
      << std::endl;
    }
    sk::rt::Lock& _lock;
    const sk::util::String _message;
  };
}

void perform()
{
  sk::rt::ReentrantLock lock;
  sk::util::ArrayList<sk::rt::Thread> threads;

  for(int counter=50; counter; --counter) {
    threads.add(new sk::rt::Thread(new Block("t" + sk::util::String::valueOf(counter), lock)));
  }

  threads.forEach(sk::rt::thread::Starter());
  sk::rt::Thread::sleep(10000);
  threads.forEach(sk::rt::thread::Stopper());

  // threads.forEach(sk::rt::thread::Joiner());
}

