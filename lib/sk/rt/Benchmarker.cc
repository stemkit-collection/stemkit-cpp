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

#include <sk/rt/Benchmarker.h>
#include <sk/rt/Benchmark.h>

#include "bm/Executor.h"

static const sk::util::String __className("sk::rt::Benchmarker");

sk::rt::Benchmarker::
Benchmarker(const sk::util::String& title)
  : _title(title), _scope(__className), _maxTitleSize(0)
{
}

sk::rt::Benchmarker::
~Benchmarker()
{
}

const sk::util::Class
sk::rt::Benchmarker::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::Benchmarker::
init()
{
  setUp();

  struct Initializer : public virtual sk::util::Processor<sk::rt::bm::Runner> {
    void process(sk::rt::bm::Runner& runner) const {
      runner.init();
    }
  };
  _runners.forEach(Initializer());
}

void
sk::rt::Benchmarker::
start() throw()
{
  struct Starter : public virtual sk::util::Processor<sk::rt::bm::Runner> {
    void process(sk::rt::bm::Runner& runner) const {
      runner.start();
    }
  };
  _scope.info(_title) << "started";
  _runners.forEach(Starter());
  _scope.info(_title) << "finished";
}

void
sk::rt::Benchmarker::
add(const sk::util::String& title, sk::rt::Benchmarkable* code)
{
  if(_maxTitleSize < title.size()) {
    _maxTitleSize = title.size();
  }
  _runners.add(new sk::rt::bm::Executor(_maxTitleSize, title, code));
}

void
sk::rt::Benchmarker::
add(const sk::util::String& title, sk::rt::Runnable* code)
{
  struct Adaptor : public sk::rt::Benchmark {
    Adaptor(sk::rt::Runnable* code) 
      : _codeHolder(code) {}

    void run() {
      _codeHolder.get().run();
    }
    sk::util::Holder<sk::rt::Runnable> _codeHolder;
  };
  add(title, new Adaptor(code));
}

void
sk::rt::Benchmarker::
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
sk::rt::Benchmarker::
add(sk::rt::bm::Runner* runner)
{
  _runners.add(runner);
}

void
sk::rt::Benchmarker::
add(sk::rt::bm::Runner& runner)
{
  _runners.add(runner);
}

namespace {
  struct Reporter : public virtual sk::util::Processor<sk::rt::bm::Runner> {
    Reporter(int indent, std::ostream& stream)
      : _indent(indent), _stream(stream) {}

    void process(sk::rt::bm::Runner& runner) const {
      runner.report(_indent, _stream);
    }
    int _indent;
    std::ostream& _stream;
  };
}

void 
sk::rt::Benchmarker::
report(int indent, std::ostream& stream) const
{
  sk::util::String prefix = sk::util::String(' ') * indent;
  stream << prefix << _title << std::endl;

  _runners.forEach(Reporter(indent + 2, stream));
}

void 
sk::rt::Benchmarker::
setUp()
{
}
