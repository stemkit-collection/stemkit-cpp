/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/SystemException.h>

#include <logger/PipeDestination.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

sk::rt::logger::PipeDestination::
PipeDestination(const logger::Destination& destination)
  : _destinationHolder(destination.clone()), _descriptor(-1)
{
}

sk::rt::logger::PipeDestination::
PipeDestination(const PipeDestination& other)
  : _destinationHolder(other._destinationHolder), _descriptor(other.cloneDescriptor())
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
  if(_descriptor < 0) {
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
  if(_descriptor < 0) {
    makePipe();
  }
  if(size > 0) {
    if(::write(_descriptor, buffer, size) < 0) {
      cleanup();
      throw sk::util::SystemException("dispatch()");
    }
  }
}

void
sk::rt::logger::PipeDestination::
makePipe()
{
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
          std::cerr << "PIPE: " << exception.what() << std::endl;
          ::_exit(5);
        }
        catch(...) {
          std::cerr << "PIPE: Unknown exception" << std::endl;
          ::_exit(5);
        }
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
    }
  }
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
      throw sk::util::SystemException("waitData()");
    }
    destination.dispatch(&buffer.front(), n);
  }
}
