/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileInputStream.h>
#include <sk/io/FileStreamCoupler.cxx>

sk::io::FileInputStream::
FileInputStream(const sk::io::File& file)
  : FileStreamCoupler<FileDescriptorInputStream>(std::auto_ptr<File>(new File(file)))
{
}

sk::io::FileInputStream::
FileInputStream(const sk::util::String& name)
  : FileStreamCoupler<FileDescriptorInputStream>(std::auto_ptr<File>(new File(name, "r")))
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

uint64_t
sk::io::FileInputStream::
available() const
{
  return getFile().size() - getFile().position();
}
