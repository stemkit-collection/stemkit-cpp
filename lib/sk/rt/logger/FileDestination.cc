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
#include <sk/util/IllegalStateException.h>
#include <sk/util/SystemException.h>
#include <sk/util/Holder.cxx>
#include <sk/rt/Locker.h>

#include <logger/FileDestination.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "StableHeadCycler.h"

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname, scope::Arbitrator& arbitrator)
  : _descriptor(-1), _cyclerHolder(new StableHeadCycler(pathname)), _arbitrator(arbitrator)
{
}

sk::rt::logger::FileDestination::
FileDestination(const Cycler& cycler, scope::Arbitrator& arbitrator)
  : _descriptor(-1), _cyclerHolder(sk::util::covariant<sk::rt::logger::Cycler>(cycler.clone())), _arbitrator(arbitrator)
{
}

sk::rt::logger::FileDestination::
FileDestination(const FileDestination& other)
  : _descriptor(other.cloneDescriptor()), _cyclerHolder(sk::util::covariant<sk::rt::logger::Cycler>(other._cyclerHolder.get().clone())), _arbitrator(other._arbitrator)
{
}

sk::rt::logger::FileDestination::
~FileDestination()
{
  closeFile();
}

void
sk::rt::logger::FileDestination::
close()
{
  closeFile();
}

const sk::util::Class
sk::rt::logger::FileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::FileDestination");
}

sk::util::Object*
sk::rt::logger::FileDestination::
clone() const
{
  return new FileDestination(*this);
}

int
sk::rt::logger::FileDestination::
cloneDescriptor() const
{
  return _descriptor < 0 ? _descriptor : dup(_descriptor);
}

const std::vector<int>
sk::rt::logger::FileDestination::
makeReady()
{
  ensureFile();

  static std::vector<int> descriptors;
  descriptors.push_back(_descriptor);

  return descriptors;
}

void
sk::rt::logger::FileDestination::
dispatch(const char* buffer, int size)
{
  sk::rt::Locker locker(_arbitrator);

  ensureFile();
  writeData(buffer, size);

  if(_cyclerHolder.getMutable().advance(size) == false) {
    writeData("[---Switched---]\n");
    closeFile();
  }
}

void
sk::rt::logger::FileDestination::
ensureFile()
{
  if(_descriptor >= 0 && _cyclerHolder.get().offset() > 0) {
    return;
  }
  closeFile();
  _cyclerHolder.getMutable().init();

  _descriptor = ::open(_cyclerHolder.get().getPath().getChars(), O_RDWR);
  if(_descriptor < 0) {
    throw sk::util::SystemException("open():" + _cyclerHolder.get().getPath());
  }
  off_t offset = ::lseek(_descriptor, 0, SEEK_END);
  if(offset == -1) {
    throw sk::util::SystemException("lseek():" + _cyclerHolder.get().getPath());
  }
  _cyclerHolder.getMutable().advance(offset);
}

void
sk::rt::logger::FileDestination::
closeFile()
{
  if(_descriptor < 0) {
    return;
  }
  ::close(_descriptor);
  _descriptor = -1;
}

void
sk::rt::logger::FileDestination::
writeData(const char* data)
{
  writeData(data, strlen(data));
}

void
sk::rt::logger::FileDestination::
writeData(const char* data, int size)
{
  if(_descriptor < 0) {
    throw sk::util::IllegalStateException("File not open:" + _cyclerHolder.get().getPath());
  }
  int offset = 0;
  while(offset < size) {
    int n = ::write(_descriptor, data + offset, size - offset);
    if(n > 0) {
      offset += n;
      continue;
    }
    if(n == 0) {
      throw sk::util::IllegalStateException("Write 0 bytes:" + _cyclerHolder.get().getPath());
    }
    if(n < 0) {
      throw sk::util::SystemException("write():" + _cyclerHolder.get().getPath());
    }
  }
}

const sk::rt::logger::Cycler&
sk::rt::logger::FileDestination::
getCycler() const
{
  return _cyclerHolder.get();
}

sk::rt::logger::Cycler&
sk::rt::logger::FileDestination::
getCycler()
{
  return _cyclerHolder.getMutable();
}
