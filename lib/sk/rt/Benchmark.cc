/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/Holder.cxx>

#include <sk/rt/Benchmark.h>
#include <sk/rt/StopWatch.h>

static const sk::util::String __className("sk::rt::Benchmark");

namespace {
  class BenchmarkItem : public virtual sk::rt::Benchmarkable {
    public:
      BenchmarkItem(const sk::rt::Scope& parent, const sk::util::String& title, sk::rt::Runnable* code)
        : _scope(parent.scope("Item")), _title(title), _codeHolder(code) {}

      void start() throw() {
        _scope.info(_title) << "started";
        try {
          sk::rt::Runnable& code = _codeHolder.get();

          _stopwatch.start();
          code.run();
          _stopwatch.stop();
        }
        catch(const std::exception& exception) {
          _stopwatch.stop();
          _scope.error(_title) << exception.what();
        }
        _scope.info(_title) << "finished: " << _stopwatch.inspect();
      }

      void report(int indent, std::ostream& stream) const {
        throw sk::util::UnsupportedOperationException(SK_METHOD);
      }

    private:
      sk::rt::Scope _scope;
      sk::util::Holder<sk::rt::Runnable> _codeHolder;
      sk::rt::StopWatch _stopwatch;
      const sk::util::String _title;
  };
}

sk::rt::Benchmark::
Benchmark(const sk::util::String& title)
  : _title(title), _scope(__className)
{
}

sk::rt::Benchmark::
~Benchmark()
{
}

const sk::util::Class
sk::rt::Benchmark::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::Benchmark::
start() throw()
{
  setUp();

  struct Performer : public virtual sk::util::Processor<Benchmarkable> {
    void process(Benchmarkable& item) const {
      item.start();
    }
  };
  _scope.info(_title) << "started";
  _items.forEach(Performer());
  _scope.info(_title) << "finished";

  tearDown();
}

void
sk::rt::Benchmark::
add(const sk::util::String& name, sk::rt::Runnable* code)
{
  _items.add(new BenchmarkItem(_scope, name, code));
}

void
sk::rt::Benchmark::
add(sk::rt::Benchmarkable* benchmark)
{
  _items.add(benchmark);
}

void 
sk::rt::Benchmark::
report(int indent, std::ostream& stream) const
{
  // throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::Benchmark::
setUp()
{
}

void
sk::rt::Benchmark::
tearDown()
{
}
