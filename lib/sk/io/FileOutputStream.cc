/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/io/FileOutputStream.h>

sk::io::FileOutputStream::
FileOutputStream(const sk::io::File& file)
  : sk::io::FileDescriptorOutputStream(file.writeDescriptor(false)), _file(file)
{
}

sk::io::FileOutputStream::
FileOutputStream(const sk::util::String& name, bool append)
  : sk::io::FileDescriptorOutputStream(sk::io::File(name).writeDescriptor(append)), _file(name)
{
}

sk::io::FileOutputStream::
~FileOutputStream()
{
}

const sk::util::Class
sk::io::FileOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::FileOutputStream");
}

const sk::io::File&
sk::io::FileOutputStream::
getFile() const
{
  return _file;
}
