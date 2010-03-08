/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/sys/Process.h>
#include <sk/io/FileInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>

#include <sk/rt/SystemException.h>

#include <iostream>
#include <string.h>

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::Strings& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(inputStream, sk::util::Strings());
}

sk::sys::Process::
Process(sk::io::InputStream& inputStream, const sk::util::Strings& cmdline)
  : _scope(*this), _listener(*this)
{
  start(inputStream, cmdline);
}

sk::sys::Process::
Process(const sk::util::Strings& cmdline, ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(cmdline);
}

sk::sys::Process::
Process(ProcessListener& listener)
  : _scope(*this), _listener(listener)
{
  start(sk::util::Strings());
}

sk::sys::Process::
Process(const sk::util::Strings& cmdline)
  : _scope(*this), _listener(*this)
{
  start(cmdline);
}

sk::sys::Process::
~Process()
{
  sk::util::Exception::guard(_scope.warning(SK_METHOD), *this, &sk::sys::Process::stop);
}

const sk::util::Class
sk::sys::Process::
getClass() const
{
  return sk::util::Class("sk::sys::Process");
}

namespace {
  struct ExecArgumentCollector : public virtual sk::util::Processor<const sk::util::String> {
    ExecArgumentCollector(std::vector<char*>& arguments)
      : _arguments(arguments) {}

    void process(const sk::util::String& item) const {
      _arguments.push_back(const_cast<char*>(item.getChars()));
    }
    std::vector<char*>& _arguments;
  };
}

void
sk::sys::Process::
start(const sk::util::Strings& cmdline)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::sys::Process::
start(sk::io::InputStream& inputStream, const sk::util::Strings& cmdline)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::sys::Process::
processStarting(sk::io::Stream& umbilical)
{
}

int
sk::sys::Process::
processStopping()
{
  return 0;
}

void
sk::sys::Process::
stop() 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::sys::Process::
processJoining() 
{
}

void
sk::sys::Process::
join()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}


bool
sk::sys::Process::
isSuccess() const
{
  return isExited() && exitStatus() == 0;
}

bool
sk::sys::Process::
isExited() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::Process::
isKilled() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::sys::Process::
ensureNotRunning() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int
sk::sys::Process::
exitStatus() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int
sk::sys::Process::
signal() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::Process::
isAlive() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

