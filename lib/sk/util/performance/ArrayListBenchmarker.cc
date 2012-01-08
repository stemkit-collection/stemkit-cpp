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

#include "ArrayListBenchmarker.h"
#include <deque>
#include <sk/util/ArrayList.cxx>

static const sk::util::String __className("sk::util::performance::ArrayListBenchmarker");

sk::util::performance::ArrayListBenchmarker::
ArrayListBenchmarker()
  : sk::rt::Benchmarker("ArrayList benchmarks")
{
}

sk::util::performance::ArrayListBenchmarker::
~ArrayListBenchmarker()
{
}

const sk::util::Class
sk::util::performance::ArrayListBenchmarker::
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

  struct StandardDequeStore : public virtual Benchmark {
    StandardDequeStore(const uint32_t iterations, std::deque<sk::util::String*>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.push_back(new sk::util::String("abc"));
      }
    }
    std::deque<sk::util::String*>& _storage;
  };

  struct StandardDequeRetriever : public virtual Benchmark {
    StandardDequeRetriever(const uint32_t iterations, std::deque<sk::util::String*>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        (*_storage.at(counter)).size();
      }
    }
    std::deque<sk::util::String*>& _storage;
  };

  struct StandardDequeCleaner : public virtual Benchmark {
    StandardDequeCleaner(const uint32_t iterations, std::deque<sk::util::String*>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      std::for_each(_storage.begin(), _storage.end(), *this);
      _storage.clear();
    }

    void operator()(sk::util::String* s) const {
      delete s;
    }
    std::deque<sk::util::String*>& _storage;
  };

  struct StemkitArrayListStore : public virtual Benchmark {
    StemkitArrayListStore(const uint32_t iterations, sk::util::ArrayList<sk::util::String>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.add(new sk::util::String("abc"));
      }
    }
    sk::util::ArrayList<sk::util::String>& _storage;
  };

  struct StemkitArrayListRetriever : public virtual Benchmark {
    StemkitArrayListRetriever(const uint32_t iterations, sk::util::ArrayList<sk::util::String>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        _storage.get(counter).size();
      }
    }
    sk::util::ArrayList<sk::util::String>& _storage;
  };

  struct StemkitArrayListCleaner : public virtual Benchmark {
    StemkitArrayListCleaner(const uint32_t iterations, sk::util::ArrayList<sk::util::String>& storage)
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      _storage.clear();
    }
    sk::util::ArrayList<sk::util::String>& _storage;
  };
}

void
sk::util::performance::ArrayListBenchmarker::
setUp()
{
  static std::deque<sk::util::String*> std_deque;
  static sk::util::ArrayList<sk::util::String> sk_array_list;

  add("Put 100,000 strings in std::deque", new StandardDequeStore(100000, std_deque));
  add("Put 100,000 strings in sk::util::ArrayList", new StemkitArrayListStore(100000, sk_array_list));

  add("Retrieve 100,000 strings in std::deque", new StandardDequeRetriever(100000, std_deque));
  add("Retrieve 100,000 strings in sk::util::ArrayList", new StemkitArrayListRetriever(100000, sk_array_list));

  add("Clear 100,000 strings in std::deque", new StandardDequeCleaner(100000, std_deque));
  add("Clear 100,000 strings in sk::util::ArrayList", new StemkitArrayListCleaner(100000, sk_array_list));
}
