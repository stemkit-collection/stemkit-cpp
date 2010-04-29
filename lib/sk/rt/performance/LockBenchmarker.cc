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
#include <sk/util/Holder.cxx>
#include <sk/rt/Benchmark.h>

#include "LockBenchmarker.h"
#include <sk/rt/ReentrantLock.h>
#include <sk/rt/Mutex.h>

static const sk::util::String __className("sk::util::performance::LockBenchmarker");

sk::util::performance::LockBenchmarker::
LockBenchmarker()
  : sk::rt::Benchmarker("lock benchmarks")
{
}

sk::util::performance::LockBenchmarker::
~LockBenchmarker()
{
}

const sk::util::Class
sk::util::performance::LockBenchmarker::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct RecursiveLockingBenchmark : public virtual sk::rt::Benchmark {
    RecursiveLockingBenchmark(sk::rt::Lock* lock)
      : _lockHolder(lock), _lock(_lockHolder.getMutable()) {}
      
    void run() {
      for(int iterations = 30000; iterations; --iterations) {
        for(int lock_counter=100; lock_counter; --lock_counter)  {
          _lock.lock();
        }
        for(int unlock_counter=100; unlock_counter; --unlock_counter)  {
          _lock.unlock();
        }
      }
    }
    sk::util::Holder<sk::rt::Lock> _lockHolder;
    sk::rt::Lock& _lock;
  };

  struct FlatLockingBenchmark : public virtual sk::rt::Benchmark {
    FlatLockingBenchmark(sk::rt::Lock* lock)
      : _lockHolder(lock), _lock(_lockHolder.getMutable()) {}
      
    void run() {
      for(int iterations = 30000; iterations; --iterations) {
        for(int lock_counter=100; lock_counter; --lock_counter)  {
          _lock.lock();
          _lock.unlock();
        }
      }
    }
    sk::util::Holder<sk::rt::Lock> _lockHolder;
    sk::rt::Lock& _lock;
  };

}

void 
sk::util::performance::LockBenchmarker::
setUp()
{
  add("ReentrantLock with recursion", new RecursiveLockingBenchmark(new sk::rt::ReentrantLock));
  add("ReentrantLock without recursion", new FlatLockingBenchmark(new sk::rt::ReentrantLock));
  add("Mutex with ownership", new FlatLockingBenchmark(new sk::rt::Mutex(true)));
  add("Mutex without ownership", new FlatLockingBenchmark(new sk::rt::Mutex(false)));
}
