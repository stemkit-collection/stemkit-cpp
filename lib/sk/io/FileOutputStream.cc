/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/io/FileStreamCoupler.cxx>
#include <sk/io/FileOutputStream.h>

sk::io::FileOutputStream::
FileOutputStream(const sk::io::File& file)
  : FileStreamCoupler<FileDescriptorOutputStream>(std::auto_ptr<File>(new File(file)))
{
}

sk::io::FileOutputStream::
FileOutputStream(const sk::util::String& name)
  : FileStreamCoupler<FileDescriptorOutputStream>(std::auto_ptr<File>(new File(name, "w")))
{
}

sk::io::FileOutputStream::
FileOutputStream(const sk::util::String& name, bool append)
  : FileStreamCoupler<FileDescriptorOutputStream>(std::auto_ptr<File>(new File(name, (append ? "a" : "w"))))
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
