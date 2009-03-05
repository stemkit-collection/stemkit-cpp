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
#include <sk/util/ArrayList.cxx>
#include <sk/rt/thread/ScopeArbitrator.h>

void perform();

int main(int argc, const char* argv[])
{
  sk::rt::Thread::setup();

  sk::rt::Scope::controller().getAggregator().setArbitrator(new sk::rt::thread::ScopeArbitrator);
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <log destination='file' level='notice' show-object='false' show-time='false' >\n\
          <file location='/tmp/gfb' name='zzz' size='50M' chunks='4' ensure-chunks='true' policy='pointing' use-pipe='false' />\n\
        </log>\n\
        \n\
      </scope>\n\
    ")
  );

  perform();

  sk::rt::Thread::reset();
}

namespace {
  struct Block : public virtual sk::rt::Runnable {
    Block(const sk::util::String& name) 
      : _scope(name) {}

    void run() {
      const sk::rt::thread::Generic& current = sk::rt::Thread::currentThread();
      sk::rt::Thread::sleep(1000);
      while(true) {
        _scope.info("Block") << "My estimation is " << 15 << " and this is final!!! " << current.inspect() ;
      }
    }
    sk::rt::Scope _scope;
  };
}

namespace {
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
void perform()
{
  sk::util::ArrayList<sk::rt::Thread> threads;

  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("aaa")));
  threads.add(new sk::rt::Thread(new Block("bbb")));
  threads.add(new sk::rt::Thread(new Block("ccc")));
  threads.add(new sk::rt::Thread(new Block("ddd")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));
  threads.add(new sk::rt::Thread(new Block("eee")));

  threads.forEach(Starter());
  threads.forEach(Joiner());
}
