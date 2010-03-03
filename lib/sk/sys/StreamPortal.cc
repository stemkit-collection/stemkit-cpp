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

sk::rt::Scope& 
sk::sys::StreamPortal::
scope() 
{
  static sk::rt::Scope scope(__className);
  return scope;
}

sk::sys::StreamPortal::
StreamPortal(sk::util::PropertyRegistry& registry)
{
  importStreams(registry);
  registry.setProperty("SK_STREAMS", "");
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
  return _streams.getMutable(index);
}

void 
sk::sys::StreamPortal::
forEachStream(const sk::util::Processor<const sk::io::Stream>& processor) const
{
  _streams.forEach(processor);
}

void 
sk::sys::StreamPortal::
importStreams(const sk::util::PropertyRegistry& registry)
{
  scope().detail(__FUNCTION__) << "SK_STREAMS: " << registry.getProperty("SK_STREAMS", "").inspect();
  descriptors(registry).forEach(StreamPortalImporter(_streams));
}

const sk::util::Strings 
sk::sys::StreamPortal::
descriptors(const sk::util::PropertyRegistry& registry)
{
  return registry.getProperty("SK_STREAMS", "").split("|");
}

void 
sk::sys::StreamPortal::
exportStreams(const sk::util::List<sk::io::Stream>& streams, sk::util::PropertyRegistry& registry)
{
  if(streams.isEmpty() == false) {
    sk::util::Strings descriptors;
    streams.forEach(StreamPortalExporter(descriptors));
    registry.setProperty("SK_STREAMS", descriptors.join("|"));
    scope().detail(__FUNCTION__) << "Setting SK_STREAMS: " << registry.getProperty("SK_STREAMS", "").inspect();
  }
  else {
    scope().detail(__FUNCTION__) << "Propagating SK_STREAMS: " << registry.getProperty("SK_STREAMS", "").inspect();
    descriptors(registry).forEach(StreamPortalPropagator());
  }
}
