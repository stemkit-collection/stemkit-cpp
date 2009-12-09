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

#include <sk/rt/StopWatch.h>
#include "Executor.h"

#include <iomanip>
#include <numeric>
#include <algorithm>

static const sk::util::String __className("sk::rt::bm::Executor");

sk::rt::bm::Executor::
Executor(const int& maxTitleSize, const sk::util::String& title, sk::rt::Benchmarkable* code)
  : _scope(__className), _maxTitleSize(maxTitleSize), _title(title), _codeHolder(code)
{
}

sk::rt::bm::Executor::
~Executor()
{
}

const sk::util::Class
sk::rt::bm::Executor::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::bm::Executor::
init() {
}

void 
sk::rt::bm::Executor::
start() throw() 
{
  _scope.info(_title) << "started";
  sk::rt::Benchmarkable& code = _codeHolder.get();
  sk::rt::StopWatch stopwatch;

  code.setup();
  stopwatch.start();

  try {
    code.run();
    stopwatch.stop();
  }
  catch(const std::exception& exception) {
    stopwatch.stop();
    _scope.error(_title) << exception.what();
  }
  _scope.info(_title) << "finished: " << stopwatch.inspect();
  _results.push_back(stopwatch.getMicroseconds());

  code.reset();
}

void 
sk::rt::bm::Executor::
report(int indent, std::ostream& stream) const 
{
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

