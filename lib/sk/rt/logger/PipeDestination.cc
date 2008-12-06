/*  vim: set sw=2:
 *
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/SystemException.h>
#include <sk/util/SystemExit.h>

#include <logger/PipeDestination.h>
#include <sk/rt/logger/Level.h>
#include <sk/rt/logger/IScope.h>
#include <sk/rt/logger/IConfig.h>
#include <sk/rt/logger/Stream.h>

#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <iostream>
#include <vector>
#include <algorithm>

sk::rt::logger::PipeDestination::
PipeDestination(const logger::Destination& destination)
  : _destinationHolder(destination.clone()), _descriptor(-1), _piped(false)
{
}

sk::rt::logger::PipeDestination::
PipeDestination(const PipeDestination& other)
  : _destinationHolder(other._destinationHolder), _descriptor(other.cloneDescriptor()), _piped(other._piped)
{
}

sk::rt::logger::PipeDestination::
~PipeDestination()
{
  cleanup();
}

void 
sk::rt::logger::PipeDestination::
cleanup()
{
  if(_descriptor >= 0) {
    ::close(_descriptor);
    _descriptor = -1;
  }
}

const sk::util::Class
sk::rt::logger::PipeDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::PipeDestination");
}

sk::rt::logger::PipeDestination*
sk::rt::logger::PipeDestination::
clone() const
{
  return new PipeDestination(*this);
}

int 
sk::rt::logger::PipeDestination::
cloneDescriptor() const
{
  return _descriptor < 0 ? _descriptor : dup(_descriptor);
}

const std::vector<int>
sk::rt::logger::PipeDestination::
makeReady()
{
  static std::vector<int> descriptors;
  if(makePipe() == true) {
    makePipe();

    descriptors.clear();
    descriptors.push_back(_descriptor);
  }
  return descriptors;
}

void
sk::rt::logger::PipeDestination::
dispatch(const char* buffer, int size)
{
  try {
    makePipe();

    if(size > 0) {
      if(::write(_descriptor, buffer, size) < 0) {
        cleanup();
        throw sk::util::SystemException("dispatch()");
      }
    }
  }
  catch(const std::exception& exception) {
    throw sk::util::SystemExit(exception);
  }
}

void
sk::rt::logger::PipeDestination::
close()
{
  ::close(_descriptor);
}

bool
sk::rt::logger::PipeDestination::
makePipe()
{
  if(_piped == true) {
    return false;
  }
  int descriptors[2];
  if(::pipe(descriptors) < 0) {
    throw sk::util::SystemException("makePipe()");
  }
  int pid = fork();
  switch(pid) {
    case 0: {
      if(fork() == 0) {
        signal(SIGPIPE, SIG_IGN);

        try {
          ::close(0);
          ::dup(descriptors[0]);

          std::vector<int> preserve = _destinationHolder.get().makeReady();
          for(int descriptor=3; descriptor < FD_SETSIZE ;descriptor++) {
            if(std::find(preserve.begin(), preserve.end(), descriptor) == preserve.end()) {
              ::close(descriptor);
            }
          }
          waitData(0);
        }
        catch(const std::exception& exception) {
          output(exception.what());
          ::_exit(5);
        }
        catch(...) {
          output("Unknown exception");
          ::_exit(5);
        }
        output("Exit");
      }
      ::_exit(0);
    }
    case -1: {
      ::close(descriptors[0]);
      ::close(descriptors[1]);

      throw sk::util::SystemException("makePipe(), fork");
    }
    default: {
      if(::waitpid(pid, 0, 0) < 0) {
        throw sk::util::SystemException("makePipe(), waitpid");
      }
      ::close(descriptors[0]);
      _descriptor = descriptors[1];
      _piped = true;
    }
  }
  return true;
}

namespace {
  struct OutputScope 
    : public virtual sk::rt::logger::IScope,
      public virtual sk::rt::logger::IConfig
  {
    OutputScope(sk::rt::logger::Destination& destination) 
      : _destination(destination) {}

    const sk::rt::logger::IConfig& getConfig() const {
      return *this;
    }
    bool checkLogLevel(const sk::rt::logger::Level& level) const {
      return true;
    }
    sk::rt::logger::Destination& getLogDestination() const {
      return _destination;
    }
    const char* getTimeFormat() const {
      return "%c";
    }
    bool isLogPid() const {
      return false;
    }
    bool isLogTime() const {
      return true;
    }
    bool isLogObject() const {
      return false;
    }
    const sk::util::Object& getObject() const {
      return *this;
    }
    void setLogDestination() {}
    void setLogLevel(const sk::rt::logger::Level& level) {}
    void setTimeFormat(const sk::util::String& format) {}
    void setLogDestination(const sk::rt::logger::Destination& destination) {}
    void setLogPid(bool status) {}
    void setLogTime(bool status) {}
    void setLogObject(bool status) {}
    void agregateScopeName(std::ostream& stream) const {
      stream << "PIPE";
    }
    sk::rt::logger::Destination& _destination;
  };
}

void
sk::rt::logger::PipeDestination::
output(const sk::util::String& message)
{
  try {
    _destinationHolder.get().dispatch("### ", 4);
    OutputScope scope(_destinationHolder.get());
    Stream stream(sk::util::String::EMPTY, logger::Level::SK_L_NOTICE, scope);

    stream << message;
  }
  catch(...) {}
}

void
sk::rt::logger::PipeDestination::
waitData(int descriptor)
{
  Destination& destination = _destinationHolder.get();

  std::vector<char> buffer(264);
  while(true) {
    int n = ::read(descriptor, &buffer.front(), buffer.size());
    if(n == 0) {
      ::close(descriptor);
      break;
    }
    if(n < 0) {
      ::close(descriptor);
      throw sk::util::SystemException("read()");
    }
    destination.dispatch(&buffer.front(), n);
  }
}
