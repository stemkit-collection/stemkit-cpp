/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileDescriptorPipe.h>

static const char* __className("sk::io::FileDescriptorPipe");

sk::io::FileDescriptorPipe::
FileDescriptorPipe(const sk::io::FileDescriptor& output, const sk::io::FileDescriptor& input)
{
  setOutputFileDescriptor(output);
  setInputFileDescriptor(input);
}

sk::io::FileDescriptorPipe::
~FileDescriptorPipe()
{
}

const sk::util::Class
sk::io::FileDescriptorPipe::
getClass() const
{
  return sk::util::Class(__className);
}
