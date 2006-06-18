/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/File.h>
#include <sk/io/IOException.h>
#include <fcntl.h>

sk::io::File::
File(const sk::util::String& name)
  : _name(name)
{
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

sk::io::FileDescriptor
sk::io::File::
readDescriptor() const
{
  int fd = ::open(_name.getChars(), O_RDONLY);
  if(fd < 0) {
    throw sk::io::IOException("open() failed");
  }
  return sk::io::FileDescriptor(fd);
}

sk::io::FileDescriptor
sk::io::File::
writeDescriptor(bool append) const
{
  int fd = ::open(_name.getChars(), O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC));
  if(fd < 0) {
    throw sk::io::IOException("open() failed");
  }
  return sk::io::FileDescriptor(fd);
}
