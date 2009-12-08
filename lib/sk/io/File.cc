/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/rt/SystemException.h>

#include <sk/io/File.h>
#include <sk/io/IOException.h>
#include <sk/io/ClosedChannelException.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/FileInfo.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

sk::io::File::
File(const sk::io::File& other)
  : _name(other.getName()), _descriptorHolder(new sk::io::FileDescriptor(other.getFileDescriptor()))
{
}

sk::io::File::
File(const sk::util::String& name)
  : _name(name)
{
  open(O_RDONLY, 0);
}

sk::io::File::
File(const sk::util::String& name, const sk::util::String& mode)
  : _name(name)
{
  open(mode, 0644);
}

sk::io::File::
File(const sk::util::String& name, const sk::util::String& mode, int permissions)
  : _name(name)
{
  open(mode, permissions);
}

sk::io::File::
File(const sk::util::String& name, int mode)
  : _name(name)
{
  open(mode, 0644);
}

sk::io::File::
File(const sk::util::String& name, int mode, int permissions)
  : _name(name)
{
  open(mode, permissions);
}

sk::io::File::
~File()
{
}

const sk::util::Class
sk::io::File::
getClass() const
{
  return sk::util::Class("sk::io::File");
}

const sk::util::String
sk::io::File::
getName() const
{
  return _name;
}

sk::io::InputStream&
sk::io::File::
inputStream() const
{
    return _inputStreamHolder.get();
}

sk::io::OutputStream&
sk::io::File::
outputStream() const
{
    return _outputStreamHolder.get();
}

void
sk::io::File::
close()
{
  _descriptorHolder.clear();
  _inputStreamHolder.clear();
  _outputStreamHolder.clear();
}

sk::io::FileDescriptor&
sk::io::File::
getFileDescriptor() const
{
  if(_descriptorHolder.isEmpty() == true) {
    throw sk::io::ClosedChannelException();
  }
  return _descriptorHolder.get();
}

void
sk::io::File::
open(const sk::util::String& mode, int permissions)
{
  open(numericMode(mode), permissions);
}

void
sk::io::File::
open(int mode, int permissions)
{
  int fd = ::open(_name.getChars(), mode, permissions);
  if(fd < 0) {
    throw sk::io::IOException(getName() + ": open() failed");
  }
  _descriptorHolder.set(new sk::io::FileDescriptor(fd));
  _inputStreamHolder.set(new sk::io::FileDescriptorInputStream(fd));
  _outputStreamHolder.set(new sk::io::FileDescriptorOutputStream(fd));

  _infoHolder.set(new sk::io::FileInfo(_name));
}

int
sk::io::File::
numericMode(const sk::util::String& mode)
{
  if(mode == "r") {
    return O_RDONLY;
  }
  if(mode == "r+") {
    return O_RDWR;
  }
  if(mode == "w") {
    return O_WRONLY | O_TRUNC | O_CREAT;
  }
  if(mode == "w+") {
    return O_RDWR | O_TRUNC | O_CREAT;
  }
  if(mode == "a") {
    return O_WRONLY | O_APPEND | O_CREAT;
  }
  if(mode == "a+") {
    return O_RDWR | O_APPEND | O_CREAT;
  }
  throw sk::io::IOException("Bad mode " + mode.inspect() + " in open()");
}

uint64_t
sk::io::File::
position() const
{
  uint64_t n = lseek(getFileDescriptor().getFileNumber(), 0, SEEK_CUR);
  if(n == -1) {
    throw sk::io::IOException(getName() + ": lseek() failed");
  }
  return n;
}

uint64_t
sk::io::File::
size() const
{
  return info().getSize();
}

bool 
sk::io::File::
exists(const sk::util::String& path)
{
  return std::ifstream(path.getChars()).good();
}

bool 
sk::io::File::
isRegular(const sk::util::String& path)
{
  return sk::io::FileInfo(path).isRegular();
}

bool 
sk::io::File::
isDirectory(const sk::util::String& path)
{
  return sk::io::FileInfo(path).isDirectory();
}

bool 
sk::io::File::
isPipe(const sk::util::String& path)
{
  return sk::io::FileInfo(path).isPipe();
}

bool 
sk::io::File::
isDevice(const sk::util::String& path)
{
  return sk::io::FileInfo(path).isDevice();
}

void 
sk::io::File::
unlink(const sk::util::String& path)
{
  if(::unlink(path.getChars()) != 0) {
    throw sk::rt::SystemException("unlink");
  }
}

void 
sk::io::File::
rename(const sk::util::String& oldpath, const sk::util::String& newpath)
{
  if(::rename(oldpath.getChars(), newpath.getChars()) != 0) {
    throw sk::rt::SystemException("rename");
  }
}

const sk::io::FileInfo&
sk::io::File::
info() const
{
  return _infoHolder.get();
}
