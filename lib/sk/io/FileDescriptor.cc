/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileDescriptor.h>
#include <sk/io/EOFException.h>
#include <sk/io/ClosedChannelException.h>
#include <sk/rt/SystemException.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

sk::io::FileDescriptor::
FileDescriptor(int fd)
  : _fd(fd)
{
}

sk::io::FileDescriptor::
FileDescriptor(const sk::io::FileDescriptor& other)
  : _fd(::dup(other._fd))
{
  if(_fd < 0) {
    throw sk::rt::SystemException("dup");
  }
}

sk::io::FileDescriptor::
~FileDescriptor()
{
  close();
}

const sk::util::Class
sk::io::FileDescriptor::
getClass() const
{
  return sk::util::Class("sk::io::FileDescriptor");
}

void 
sk::io::FileDescriptor::
close()
{
  if(_fd < 0) {
    return;
  }
  ::close(_fd);
  _fd = -1;
}

int 
sk::io::FileDescriptor::
read(char* buffer, int offset, int length)
{
  if(_fd < 0) {
    throw sk::io::ClosedChannelException();
  }
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }
  while(true) {
    int n = ::read(_fd, buffer + offset, length);
    if(n == 0) {
      throw sk::io::EOFException();
    }
    if(n < 0) {
      if(errno != EAGAIN) {
        throw sk::rt::SystemException("read");
      }
    }
    return n;
  }
}

int
sk::io::FileDescriptor::
write(const char* buffer, int offset, int length)
{
  if(_fd < 0) {
    throw sk::io::ClosedChannelException();
  }
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }
  while(true) {
    int n = ::write(_fd, buffer + offset, length);
    if(n < 0) {
      if(errno == EAGAIN) {
        continue;
      }
      throw sk::rt::SystemException("write");
    }
    return n;
  }
}

int
sk::io::FileDescriptor::
getFileNumber() const
{
  return _fd;
}

void 
sk::io::FileDescriptor::
inheritable(bool state)
{
  int flags = fcntl(_fd, F_GETFD);
  if(flags == -1) {
    throw sk::rt::SystemException("fcntl:F_GETFD");
  }
  if(state == false) {
    flags |= FD_CLOEXEC;
  }
  else {
    flags &= ~(FD_CLOEXEC);
  }
  if(fcntl(_fd, F_SETFD, flags) == -1) {
    throw sk::rt::SystemException("fcntl:F_SETFD");
  }
}
