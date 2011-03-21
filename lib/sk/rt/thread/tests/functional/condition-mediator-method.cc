/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/util/ArrayList.cxx>
#include <sk/util/Integers.h>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

#include <sk/rt/Thread.h>
#include <sk/rt/thread/ScopeArbitrator.h>
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/thread/Starter.h>
#include <sk/rt/thread/Stopper.h>
#include <sk/rt/thread/Joiner.h>

void perform();

int main(int argc, const char* const argv[])
{
  sk::rt::Thread::setup();
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <log destination='std::cerr' level='info' show-object='false' show-time='true' />\n\
        <scope name='sk::rt::thread::pthreads'>\n\
          <log level='error' />\n\
        </scope>\n\
        <scope name='sk::rt::thread::pthreads::Thread'>\n\
          <log level='error' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );
  sk::rt::Scope::controller().getAggregator().setArbitrator(new sk::rt::thread::ScopeArbitrator);

  perform();
  sk::rt::Thread::reset();
}

namespace {
  class Workshop {
    public: 
      Workshop()
        : _scope("Workshop"), _mediator(_mutex) {}

      void printBunch(sk::rt::thread::Condition& condition) {
        _scope.info() << "Checking for a bunch";
        condition.ensure(_depot.size() >= 10);

        _scope.info() << "Got a bunch of 10: " << _depot.inspect();
        _depot.clear();
        sk::rt::Thread::sleep(5000);
      }

      void pushValue(sk::rt::thread::Condition& condition, int value) {
        _scope.info() << "...Pushing " << value;
        _depot.add(value);
        condition.announce(_depot.size() >= 10);
      }

      sk::rt::thread::ConditionMediator& mediator() {
        return _mediator;
      }

    private:
      sk::rt::Mutex _mutex;
      sk::rt::thread::ConditionMediator _mediator;
      sk::util::Integers _depot;
      sk::rt::Scope _scope;
  };

  struct Consumer : public virtual sk::rt::Runnable {
    Consumer(Workshop& workshop) 
      : _scope("Consumer"), _workshop(workshop) {}

    void run() {
      _scope.info() << sk::rt::Thread::currentThread().inspect();
      while(true) {
        _workshop.mediator().synchronize(_workshop, &Workshop::printBunch);
      }
    }
    sk::rt::Scope _scope;
    Workshop& _workshop;
  };

  struct Supplier : public virtual sk::rt::Runnable {
    Supplier(Workshop& workshop) 
      : _scope("Supplier"), _workshop(workshop), _counter(0) {}

    void run() {
      _scope.info() << sk::rt::Thread::currentThread().inspect();
      while(true) {
        _workshop.mediator().synchronize(_workshop, &Workshop::pushValue, _counter++);
        sk::rt::Thread::sleep(1000);
      }
    }
    sk::rt::Scope _scope;
    Workshop& _workshop;
    int _counter;
  };
}

void perform()
{
  Workshop workshop;

  Consumer consumer(workshop);
  Supplier supplier(workshop);

  sk::util::ArrayList<sk::rt::Thread> threads;
  threads.add(new sk::rt::Thread(consumer));
  threads.add(new sk::rt::Thread(supplier));

  threads.forEach(sk::rt::thread::Starter());
  threads.forEach(sk::rt::thread::Joiner());
}
