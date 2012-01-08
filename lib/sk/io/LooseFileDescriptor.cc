/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/LooseFileDescriptor.h>
#include <sk/io/EOFException.h>
#include <sk/io/IOException.h>
#include <sk/io/ClosedChannelException.h>
#include <sk/rt/SystemException.h>
#include <sk/util/IllegalArgumentException.h>
#include <errno.h>
#include <unistd.h>

sk::io::LooseFileDescriptor::
LooseFileDescriptor(int fd)
  : _fd(fd)
{
  if(_fd < 0) {
    throw sk::util::IllegalArgumentException(SK_METHOD);
  }
}

sk::io::LooseFileDescriptor::
LooseFileDescriptor(const sk::io::LooseFileDescriptor& other)
  : _fd(other.getFileNumber())
{
}

sk::io::LooseFileDescriptor::
~LooseFileDescriptor()
{
}

const sk::util::Class
sk::io::LooseFileDescriptor::
getClass() const
{
  return sk::util::Class("sk::io::LooseFileDescriptor");
}

void
sk::io::LooseFileDescriptor::
close()
{
  if(_fd < 0) {
    return;
  }
  ::close(_fd);
  _fd = -1;
}

int
sk::io::LooseFileDescriptor::
read(char* buffer, int offset, int length)
{
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }

  int fd = getFileNumber();
  while(true) {
    int n = ::read(fd, buffer + offset, length);
    if(n == 0) {
      throw sk::io::EOFException();
    }
    if(n < 0) {
      if(errno == EAGAIN) {
        continue;
      }
      throw sk::io::IOException("read");
    }
    return n;
  }
}

int
sk::io::LooseFileDescriptor::
write(const char* buffer, int offset, int length)
{
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }
  int fd = getFileNumber();
  while(true) {
    int n = ::write(fd, buffer + offset, length);
    if(n < 0) {
      if(errno == EAGAIN) {
        continue;
      }
      throw sk::io::IOException("write");
    }
    return n;
  }
}

int
sk::io::LooseFileDescriptor::
getFileNumber() const
{
  if(_fd < 0) {
    throw sk::io::ClosedChannelException();
  }
  return _fd;
}

sk::io::LooseFileDescriptor
sk::io::LooseFileDescriptor::
duplicateLoose() const
{
  int fd = ::dup(getFileNumber());
  if(fd < 0) {
    throw sk::rt::SystemException("dup");
  }
  return LooseFileDescriptor(fd);
}

sk::io::LooseFileDescriptor&
sk::io::LooseFileDescriptor::
reopen(const sk::io::LooseFileDescriptor& other)
{
  int fd = getFileNumber();
  int other_fd = other.getFileNumber();

  close();

  _fd = ::dup2(other_fd, fd);
  if(_fd != fd) {
    throw sk::rt::SystemException("dup2");
  }
  return *this;
}

const sk::util::String
sk::io::LooseFileDescriptor::
inspect() const
{
  return "<" + getClass().getName() + ":fd=" + sk::util::String::valueOf(getFileNumber()) + ">";
}
