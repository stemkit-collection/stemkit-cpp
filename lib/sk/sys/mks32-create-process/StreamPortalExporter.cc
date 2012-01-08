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

#include "../StreamPortalExporter.h"
#include <sk/sys/StreamPortal.h>
#include <sk/io/FileDescriptor.h>
#include <sk/io/FileDescriptorProvider.h>
#include <winnutc.h>

static const char* __className("sk::sys::StreamPortalExporter");

sk::sys::StreamPortalExporter::
StreamPortalExporter(sk::util::Strings& descriptors)
  : _descriptors(descriptors)
{
}

const sk::util::Class
sk::sys::StreamPortalExporter::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::sys::StreamPortalExporter::
process(const sk::io::Stream& stream) const
{
  int fd = _propagator.propagate(sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor().getFileNumber());
  sk::sys::StreamPortal::scope().detail(__className) << "F: " << fd << ", H: " << ::_NutFdToHandle(fd);
  _descriptors << sk::util::String::valueOf(reinterpret_cast<int>(::_NutFdToHandle(fd)));
}
