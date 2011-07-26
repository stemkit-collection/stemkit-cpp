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
#include <sk/util/InsufficientMemoryException.h>
#include <sk/rt/Benchmark.h>
#include <memory.h>
#include <stdlib.h>
#include <strings.h>

#include "LinkedListBenchmarker.h"
#include <list>
#include <sk/util/LinkedList.cxx>

static const sk::util::String __className("sk::util::performance::LinkedListBenchmarker");

sk::util::performance::LinkedListBenchmarker::
LinkedListBenchmarker()
  : sk::rt::Benchmarker("LinkedList benchmarks")
{
}

sk::util::performance::LinkedListBenchmarker::
~LinkedListBenchmarker()
{
}

const sk::util::Class
sk::util::performance::LinkedListBenchmarker::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct Benchmark : public virtual sk::rt::Benchmark {
    Benchmark(const uint32_t iterations) 
      : _iterations(iterations) {}

    void run() {
      run(_iterations);
    }
    virtual void run(const uint32_t iterations) = 0;
    const uint32_t _iterations;
  };

  struct StandardListStore : public virtual Benchmark {
    StandardListStore(const uint32_t iterations, std::list<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.push_back(new sk::util::String("abc"));
      }
    }
    std::list<sk::util::String*>& _storage;
  };

  struct StandardListRetriever : public virtual Benchmark {
    StandardListRetriever(const uint32_t iterations, std::list<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        std::list<sk::util::String*>::iterator iterator = _storage.begin();
        for(int index = counter; index; --index) {
          ++iterator;
        }
        (*iterator)->size();
      }
    }
    std::list<sk::util::String*>& _storage;
  };

  struct StandardListCleaner : public virtual Benchmark {
    StandardListCleaner(const uint32_t iterations, std::list<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      std::for_each(_storage.begin(), _storage.end(), *this);
      _storage.clear();
    }

    void operator()(sk::util::String* s) const {
      delete s;
    }
    std::list<sk::util::String*>& _storage;
  };

  struct StemkitLinkedListStore : public virtual Benchmark {
    StemkitLinkedListStore(const uint32_t iterations, sk::util::LinkedList<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.add(new sk::util::String("abc"));
      }
    }
    sk::util::LinkedList<sk::util::String>& _storage;
  };

  struct StemkitLinkedListRetriever : public virtual Benchmark {
    StemkitLinkedListRetriever(const uint32_t iterations, sk::util::LinkedList<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        _storage.get(counter).size();
      }
    }
    sk::util::LinkedList<sk::util::String>& _storage;
  };

  struct StemkitLinkedListCleaner : public virtual Benchmark {
    StemkitLinkedListCleaner(const uint32_t iterations, sk::util::LinkedList<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      _storage.clear();
    }
    sk::util::LinkedList<sk::util::String>& _storage;
  };
}

void 
sk::util::performance::LinkedListBenchmarker::
setUp()
{
  static std::list<sk::util::String*> std_list;
  static sk::util::LinkedList<sk::util::String> sk_linked_list;

  add("Put 100,000 strings in std::list", new StandardListStore(100000, std_list));
  add("Put 100,000 strings in sk::util::LinkedList", new StemkitLinkedListStore(100000, sk_linked_list));

  // add("Retrieve 100,000 strings in std::list", new StandardListRetriever(100000, std_list));
  // add("Retrieve 100,000 strings in sk::util::LinkedList", new StemkitLinkedListRetriever(100000, sk_linked_list));

  add("Clear 100,000 strings in std::list", new StandardListCleaner(100000, std_list));
  add("Clear 100,000 strings in sk::util::LinkedList", new StemkitLinkedListCleaner(100000, sk_linked_list));
}
