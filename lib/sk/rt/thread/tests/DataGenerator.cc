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
#include <sk/util/ArrayList.cxx>

#include "DataGenerator.h"

static const sk::util::Class __class("sk::rt::thread::tests::DataGenerator");

sk::rt::thread::tests::DataGenerator::
DataGenerator(int workforce, std::vector<int>& target)
  : _workforce(workforce), _target(target)
{
}

sk::rt::thread::tests::DataGenerator::
~DataGenerator()
{
}

const sk::util::Class
sk::rt::thread::tests::DataGenerator::
getClass() const
{
  return __class;
}

namespace {
  struct Worker : public virtual sk::rt::Runnable {
    Worker(int id, int amount, int runs, std::vector<int>& target)
      : _id(id), _amount(amount), _runs(runs), _target(target) {}

    void run() const {
      for(int counter=0; counter < _runs ; ++counter) {
        fill();
        sk::rt::Thread::yield();
      }
    }

    void fill() const {
      for(int counter=0; counter < _amount ; ++counter) {
        _target.push_back(_id);
      }
    }

    int _id;
    int _amount;
    int _runs;
    std::vector<int>& _target;
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
sk::rt::thread::tests::DataGenerator::
fill(int amount, int runs)
{
  for(int counter=0; counter < _workforce ;++counter) {
    _threads.add(new Thread(new Worker(counter, amount, runs, _target)));
  }
  _threads.forEach(Starter());
  _threads.forEach(Joiner());
}

