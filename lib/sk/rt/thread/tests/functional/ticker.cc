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

#include <sk/rt/ReentrantLock.h>
#include <sk/rt/Mutex.h>
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
  sk::rt::Scope scope("main");

  perform();

  scope.info() << "DONE";
  sk::rt::Thread::reset();
  scope.info() << "RESET";
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block(const sk::util::String& message, sk::rt::Lock& lock)
      : _message(message), _lock(lock) {}

    void run() {
      while(true) {
        _lock.synchronize(*this, &Block::tick);
        sk::rt::Thread::sleep(2000);
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

namespace {
  struct Starter : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.start();
      sk::rt::Thread::sleep(1000);
    }
  };
  struct Stopper : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.stop();
    }
  };
  struct Joiner : public virtual sk::util::Processor<sk::rt::Thread> {
    void process(sk::rt::Thread& thread) const {
      thread.join();
    }
  };
}

void perform() 
{
  sk::rt::ReentrantLock lock;
  sk::util::ArrayList<sk::rt::Thread> threads;

  threads.add(new sk::rt::Thread(new Block("aaa", lock)));
  threads.add(new sk::rt::Thread(new Block("bbb", lock)));
  threads.add(new sk::rt::Thread(new Block("ccc", lock)));
  threads.add(new sk::rt::Thread(new Block("ccc", lock)));
  threads.add(new sk::rt::Thread(new Block("ccc", lock)));
  threads.add(new sk::rt::Thread(new Block("ccc", lock)));

  threads.forEach(Starter());
  // threads.forEach(Joiner());

  sleep(10);
  threads.forEach(Stopper());
}

