/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/ArrayList.cxx>
#include <sk/io/FileDescriptorInputStream.h>

#include "../StreamPortalImporter.h"

static const char* __className("sk::sys::StreamPortalImporter");

sk::sys::StreamPortalImporter::
StreamPortalImporter(sk::util::ArrayList<sk::io::Stream>& streams)
  : _streams(streams) 
{
}

const sk::util::Class
sk::sys::StreamPortalImporter::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::sys::StreamPortalImporter::
process(const sk::util::String& descriptor) const 
{
  int fd = sk::util::Integer::parseInt(descriptor);
  _streams.add(new sk::io::FileDescriptorInputStream(fd));
}
