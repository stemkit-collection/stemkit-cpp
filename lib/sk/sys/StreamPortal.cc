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
#include <sk/util/Integer.h>
#include <sk/util/ArrayList.cxx>
#include <sk/rt/SystemException.h>

#include <sk/sys/StreamPortal.h>

#include "StreamPortalImporter.h"
#include "StreamPortalExporter.h"
#include "StreamPortalPropagator.h"

static const char* __className("sk::sys::StreamPortal");

sk::sys::StreamPortal::
StreamPortal(const sk::util::PropertyRegistry& registry)
{
  importStreams(registry);
}

sk::sys::StreamPortal::
~StreamPortal()
{
}

const sk::util::Class
sk::sys::StreamPortal::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::sys::StreamPortal::
size() const
{
  return _streams.size();
}

sk::io::Stream& 
sk::sys::StreamPortal::
getStream(int index) const
{
  return _streams.get(index);
}

void 
sk::sys::StreamPortal::
forEachStream(const sk::util::Processor<sk::io::Stream>& processor) const
{
  _streams.forEach(processor);
}

void 
sk::sys::StreamPortal::
importStreams(const sk::util::PropertyRegistry& registry)
{
  descriptors(registry).forEach(StreamPortalImporter(_streams));
}

const sk::util::StringArray 
sk::sys::StreamPortal::
descriptors(const sk::util::PropertyRegistry& registry)
{
  return sk::util::StringArray::parse(registry.getProperty("SK_STREAMS", ""), "|");
}

void 
sk::sys::StreamPortal::
exportStreams(const sk::util::List<const sk::io::Stream>& streams, sk::util::PropertyRegistry& registry)
{
  if(streams.isEmpty() == false) {
    sk::util::StringArray descriptors;
    streams.forEach(StreamPortalExporter(descriptors));
    registry.setProperty("SK_STREAMS", descriptors.join("|"));
  }
  else {
    descriptors(registry).forEach(StreamPortalPropagator());
  }
}
