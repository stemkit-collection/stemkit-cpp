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

sk::io::FileDescriptor::
FileDescriptor(int fd)
  : sk::io::LooseFileDescriptor(fd)
{
}

sk::io::FileDescriptor::
FileDescriptor(const sk::io::FileDescriptor& other)
  // For some weird reason Visual Studio compiled code crashes when
  // just other.duplicateLoose() is used instead of getFileNumber().
  : sk::io::LooseFileDescriptor(other.duplicateLoose().getFileNumber())
{
}

sk::io::FileDescriptor::
FileDescriptor(const sk::io::LooseFileDescriptor& other)
  // For some weird reason Visual Studio compiled code crashes when
  // just other.duplicateLoose() is used instead of getFileNumber().
  : sk::io::LooseFileDescriptor(other.duplicateLoose().getFileNumber())
{
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
