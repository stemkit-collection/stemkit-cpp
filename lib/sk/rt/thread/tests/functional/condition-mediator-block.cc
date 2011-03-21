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
      </scope>\n\
    ")
  );
  sk::rt::Scope::controller().getAggregator().setArbitrator(new sk::rt::thread::ScopeArbitrator);

  perform();
  sk::rt::Thread::reset();
}

namespace {
  struct Consumer : public virtual sk::rt::Runnable, public virtual sk::rt::thread::Conditional {
    Consumer(sk::rt::thread::ConditionMediator& mediator, sk::util::Integers& depot) 
      : _scope("Consumer"), _mediator(mediator), _depot(depot) {}

    void process(sk::rt::thread::Condition& condition) const {
      _scope.info() << "Checking for a bunch";
      condition.ensure(_depot.size() >= 10);
      _scope.info() << "Got a bunch of 10: " << _depot.inspect();
      _depot.clear();
      sk::rt::Thread::sleep(5000);
    }

    void run() {
      _scope.info() << sk::rt::Thread::currentThread().inspect();
      while(true) {
        _mediator.synchronize(*this);
      }
    }
    sk::rt::Scope _scope;
    sk::rt::thread::ConditionMediator& _mediator;
    sk::util::Integers& _depot;
  };

  struct Supplier : public virtual sk::rt::Runnable, public virtual sk::rt::thread::Conditional {
    Supplier(sk::rt::thread::ConditionMediator& mediator, sk::util::Integers& depot) 
      : _scope("Supplier"), _mediator(mediator), _depot(depot), _counter(0) {}

    void process(sk::rt::thread::Condition& condition) const {
      _scope.info() << "...Pushing " << _counter;
      _depot.add(_counter);
      condition.announce(_depot.size() >= 10);
    }

    void run() {
      _scope.info() << sk::rt::Thread::currentThread().inspect();
      while(true) {
        _mediator.synchronize(*this);
        sk::rt::Thread::sleep(1000);
        _counter++;
      }
    }
    sk::rt::Scope _scope;
    sk::rt::thread::ConditionMediator& _mediator;
    sk::util::Integers& _depot;
    int _counter;
  };
}

void perform()
{
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);
  sk::util::Integers depot;

  Consumer consumer(mediator, depot);
  Supplier supplier(mediator, depot);

  sk::util::ArrayList<sk::rt::Thread> threads;
  threads.add(new sk::rt::Thread(consumer));
  threads.add(new sk::rt::Thread(supplier));

  threads.forEach(sk::rt::thread::Starter());
  threads.forEach(sk::rt::thread::Joiner());
}
