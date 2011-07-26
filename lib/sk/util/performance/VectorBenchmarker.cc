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
#include <sk/util/IllegalStateException.h>
#include <sk/rt/Benchmark.h>
#include <memory.h>
#include <stdlib.h>
#include <strings.h>

#include "VectorBenchmarker.h"
#include <vector>
#include <sk/util/Vector.cxx>

static const sk::util::String __className("sk::util::performance::VectorBenchmarker");

sk::util::performance::VectorBenchmarker::
VectorBenchmarker()
  : sk::rt::Benchmarker("Vector benchmarks")
{
}

sk::util::performance::VectorBenchmarker::
~VectorBenchmarker()
{
}

const sk::util::Class
sk::util::performance::VectorBenchmarker::
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

  struct StandardVectorStore : public virtual Benchmark {
    StandardVectorStore(const uint32_t iterations, std::vector<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.push_back(new sk::util::String("abc"));
      }
    }
    std::vector<sk::util::String*>& _storage;
  };

  struct StandardVectorRetriever : public virtual Benchmark {
    StandardVectorRetriever(const uint32_t iterations, const std::vector<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        (*_storage.at(counter)).size();
      }
    }
    const std::vector<sk::util::String*>& _storage;
  };

  struct StandardVectorAlgorithmChecker : public virtual Benchmark {
    StandardVectorAlgorithmChecker(const uint32_t iterations, const std::vector<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    struct Checker {
      Checker() 
        : _value("zzz") {}

      bool operator()(const sk::util::String* s) const {
        return (*s).equals(_value);
      }
      const sk::util::String _value;
    };

    void run(const uint32_t iterations) {
      (*_storage.at(iterations - 3)) = "zzz";
      Checker checker;

      for(int counter = 0; counter < 10; ++counter) {
        if(std::find_if(_storage.begin(), _storage.end(), checker) == _storage.end()) {
          throw sk::util::IllegalStateException("Expected element not found");
        }
      }
    }
    const std::vector<sk::util::String*>& _storage;
  };

  struct StandardVectorIteratorChecker : public virtual Benchmark {
    StandardVectorIteratorChecker(const uint32_t iterations, const std::vector<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      (*_storage.at(iterations - 3)) = "zzz";
      const sk::util::String value("zzz");

      for(int counter = 0; counter < 10; ++counter) {
        bool found = false;
        for(std::vector<sk::util::String*>::const_iterator iterator = _storage.begin(); iterator != _storage.end(); ++iterator) {
          if((*iterator)->equals(value) == true) {
            found = true;
            break;
          }
        }
        if(found == false) {
          throw sk::util::IllegalStateException("Expected element not found");
        }
      }
    }
    const std::vector<sk::util::String*>& _storage;
  };

  struct StandardVectorCleaner : public virtual Benchmark {
    StandardVectorCleaner(const uint32_t iterations, std::vector<sk::util::String*>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      std::for_each(_storage.begin(), _storage.end(), *this);
      _storage.clear();
    }

    void operator()(sk::util::String* s) const {
      delete s;
    }
    std::vector<sk::util::String*>& _storage;
  };

  struct StemkitVectorStore : public virtual Benchmark {
    StemkitVectorStore(const uint32_t iterations, sk::util::Vector<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = iterations; counter; --counter) {
        _storage.add(new sk::util::String("abc"));
      }
    }
    sk::util::Vector<sk::util::String>& _storage;
  };

  struct StemkitVectorRetriever : public virtual Benchmark {
    StemkitVectorRetriever(const uint32_t iterations, const sk::util::Vector<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      for(int counter = 0; counter < iterations; ++counter) {
        _storage.get(counter).size();
      }
    }
    const sk::util::Vector<sk::util::String>& _storage;
  };

  struct StemkitVectorChecker : public virtual Benchmark {
    StemkitVectorChecker(const uint32_t iterations, const sk::util::Vector<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      _storage.getMutable(iterations - 3) = "zzz";
      sk::util::String value("zzz");

      for(int counter = 0; counter < 10; ++counter) {
        if(_storage.contains(sk::util::selector::EqualValue<sk::util::String>(value)) == false) {
          throw sk::util::IllegalStateException("Expected element not found");
        }
      }
    }
    const sk::util::Vector<sk::util::String>& _storage;
  };

  struct StemkitVectorCleaner : public virtual Benchmark {
    StemkitVectorCleaner(const uint32_t iterations, sk::util::Vector<sk::util::String>& storage) 
      : Benchmark(iterations), _storage(storage) {}

    void run(const uint32_t iterations) {
      _storage.clear();
    }
    sk::util::Vector<sk::util::String>& _storage;
  };
}

void 
sk::util::performance::VectorBenchmarker::
setUp()
{
  static std::vector<sk::util::String*> std_vector;
  static sk::util::Vector<sk::util::String> sk_vector;

  add("Put 100,000 strings in std::vector", new StandardVectorStore(100000, std_vector));
  add("Put 100,000 strings in sk::util::Vector", new StemkitVectorStore(100000, sk_vector));

  add("Retrieve 100,000 strings in std::vector", new StandardVectorRetriever(100000, std_vector));
  add("Retrieve 100,000 strings in sk::util::Vector", new StemkitVectorRetriever(100000, sk_vector));

  add("Check 100,000 strings in std::vector with algorithm", new StandardVectorAlgorithmChecker(100000, std_vector));
  add("Check 100,000 strings in std::vector with iterator", new StandardVectorIteratorChecker(100000, std_vector));
  add("Check 100,000 strings in sk::util::Vector", new StemkitVectorChecker(100000, sk_vector));

  add("Clear 100,000 strings in std::vector", new StandardVectorCleaner(100000, std_vector));
  add("Clear 100,000 strings in sk::util::Vector", new StemkitVectorCleaner(100000, sk_vector));
}
