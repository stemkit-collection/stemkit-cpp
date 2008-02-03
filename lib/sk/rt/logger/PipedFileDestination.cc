/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/SystemException.h>

#include <sk/rt/logger/PipedFileDestination.h>
#include <sk/rt/logger/DirectFileDestination.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <vector>

sk::rt::logger::PipedFileDestination::
PipedFileDestination(const sk::util::Pathname& pathname)
  : FileDestination(pathname), _descriptor(-1)
{
}

sk::rt::logger::PipedFileDestination::
PipedFileDestination(const PipedFileDestination& other)
  : FileDestination(other), _descriptor(-1)
{
}

sk::rt::logger::PipedFileDestination::
~PipedFileDestination()
{
  cleanup();
}

void 
sk::rt::logger::PipedFileDestination::
cleanup()
{
  if(_descriptor >= 0) {
    ::close(_descriptor);
    _descriptor = -1;
  }
}

const sk::util::Class
sk::rt::logger::PipedFileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::PipedFileDestination");
}

sk::rt::logger::PipedFileDestination*
sk::rt::logger::PipedFileDestination::
clone() const
{
  return new PipedFileDestination(*this);
}

void
sk::rt::logger::PipedFileDestination::
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
sk::rt::logger::PipedFileDestination::
makePipe()
{
  int descriptors[2];
  if(::pipe(descriptors) < 0) {
    throw sk::util::SystemException("makePipe()");
  }
  int pid = fork();
  switch(pid) {
    case 0: {
      setpgrp();
      setsid();

      if(fork() == 0) {
        ::close(descriptors[1]);
        waitData(descriptors[0]);
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
sk::rt::logger::PipedFileDestination::
waitData(int descriptor)
{
  DirectFileDestination destination(getPathname());
  destination.setSize(getSize());
  destination.setBackups(getBackups());

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
