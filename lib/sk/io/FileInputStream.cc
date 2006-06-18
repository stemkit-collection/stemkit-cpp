/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileInputStream.h>

sk::io::FileInputStream::
FileInputStream(const sk::io::File& file)
  : sk::io::FileDescriptorInputStream(file.readDescriptor()), _file(file)
{
}

sk::io::FileInputStream::
FileInputStream(const sk::util::String& name)
  : sk::io::FileDescriptorInputStream(sk::io::File(name).readDescriptor()), _file(name)
{
}

sk::io::FileInputStream::
~FileInputStream()
{
}

const sk::util::Class
sk::io::FileInputStream::
getClass() const
{
  return sk::util::Class("sk::io::FileInputStream");
}

const sk::io::File&
sk::io::FileInputStream::
getFile() const
{
  return _file;
}
