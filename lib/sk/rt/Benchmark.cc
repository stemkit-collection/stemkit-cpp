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

#include <iomanip>
#include <numeric>

static const sk::util::String __className("sk::rt::Benchmark");

namespace {
  class BenchmarkItem : public virtual sk::rt::Benchmarkable {
    public:
      BenchmarkItem(const sk::rt::Scope& parent, const int& maxTitleSize, const sk::util::String& title, sk::rt::Runnable* code)
        : _scope(parent.scope("Item")), _maxTitleSize(maxTitleSize), _title(title), _codeHolder(code) {}

      void init() {
      }

      void start() throw() {
        _scope.info(_title) << "started";
        sk::rt::Runnable& code = _codeHolder.get();
        sk::rt::StopWatch stopwatch;

        try {
          stopwatch.start();
          code.run();
          stopwatch.stop();
        }
        catch(const std::exception& exception) {
          stopwatch.stop();
          _scope.error(_title) << exception.what();
        }
        _scope.info(_title) << "finished: " << stopwatch.inspect();
        _results.push_back(stopwatch.getMicroseconds());
      }

      void report(int indent, std::ostream& stream) const {
        sk::util::String prefix = sk::util::String(' ') * indent;
        stream << prefix << std::setw(_maxTitleSize) << _title << ":";
        size_t size = _results.size();
        switch(size) {
          case 0:
            stream << " <not mesured yet>";
            break;

          case 1:
            stream << ' ' << sk::rt::StopWatch::toString(_results[0]);
            break;

          default:
            stream << " min => " << sk::rt::StopWatch::toString(*std::min_element(_results.begin(), _results.end()));
            stream << " max => " << sk::rt::StopWatch::toString(*std::max_element(_results.begin(), _results.end()));

            if(size > 2) {
              uint64_t average = std::accumulate(_results.begin(), _results.end(), 0) / size;
              stream << ' ' << size << " => " << sk::rt::StopWatch::toString(average);
            }
        }
        stream << std::endl;
      }

    private:
      sk::rt::Scope _scope;
      sk::util::Holder<sk::rt::Runnable> _codeHolder;
      const sk::util::String _title;
      const int& _maxTitleSize;
      std::vector<uint64_t> _results;
  };
}

sk::rt::Benchmark::
Benchmark(const sk::util::String& title)
  : _title(title), _scope(__className), _maxTitleSize(0)
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
init()
{
  setUp();

  struct Initializer : public virtual sk::util::Processor<Benchmarkable> {
    void process(Benchmarkable& item) const {
      item.init();
    }
  };
  _items.forEach(Initializer());
}

void
sk::rt::Benchmark::
start() throw()
{
  struct Performer : public virtual sk::util::Processor<Benchmarkable> {
    void process(Benchmarkable& item) const {
      item.start();
    }
  };
  _scope.info(_title) << "started";
  _items.forEach(Performer());
  _scope.info(_title) << "finished";
}

void
sk::rt::Benchmark::
add(const sk::util::String& title, sk::rt::Runnable* code)
{
  if(_maxTitleSize < title.size()) {
    _maxTitleSize = title.size();
  }
  _items.add(new BenchmarkItem(_scope, _maxTitleSize, title, code));
}

void
sk::rt::Benchmark::
add(const sk::util::String& title, function_t code)
{
  struct FunctionAdaptor : public sk::rt::Runnable {
    FunctionAdaptor(function_t* code) 
      : _code(code) {}

    void run() {
      _code();
    }
    function_t* _code;
  };
  add(title, new FunctionAdaptor(code));
}

void
sk::rt::Benchmark::
add(sk::rt::Benchmarkable* benchmark)
{
  _items.add(benchmark);
}

void
sk::rt::Benchmark::
add(sk::rt::Benchmarkable& benchmark)
{
  _items.add(benchmark);
}

namespace {
  struct Reporter : public virtual sk::util::Processor<sk::rt::Benchmarkable> {
    Reporter(int indent, std::ostream& stream)
      : _indent(indent), _stream(stream) {}

    void process(sk::rt::Benchmarkable& benchmark) const {
      benchmark.report(_indent, _stream);
    }
    int _indent;
    std::ostream& _stream;
  };
}

void 
sk::rt::Benchmark::
report(int indent, std::ostream& stream) const
{
  sk::util::String prefix = sk::util::String(' ') * indent;
  stream << prefix << _title << std::endl;

  _items.forEach(Reporter(indent + 2, stream));
}

void 
sk::rt::Benchmark::
setUp()
{
}
