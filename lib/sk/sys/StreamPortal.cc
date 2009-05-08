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
#include <sk/io/FileDescriptorInputStream.h>

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

namespace {
  struct StreamImporter : public virtual sk::util::Processor<const sk::util::String> {
    StreamImporter(sk::util::ArrayList<sk::io::Stream>& streams)
      : _streams(streams) {}

    void process(const sk::util::String& descriptor) const {
      int fd = sk::util::Integer::parseInt(descriptor);
      _streams.add(new sk::io::FileDescriptorInputStream(fd));
    }

    sk::util::ArrayList<sk::io::Stream>& _streams;
  };

  struct DescriptorPropagator : public virtual sk::util::Processor<const sk::util::String> {
    void process(const sk::util::String& descriptor) const {
      propagate(sk::util::Integer::parseInt(descriptor));
    }

    int propagate(int fd) const {
      sk::io::LooseFileDescriptor descriptor(fd);
      descriptor.inheritable(true);

      return fd;
    }
  };

  struct StreamExporter : public virtual sk::util::Processor<const sk::io::Stream> {
    StreamExporter(sk::util::StringArray& descriptors)
      : _descriptors(descriptors) {}

    void process(const sk::io::Stream& stream) const {
      int fd = _propagator.propagate(sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor().getFileNumber());
      _descriptors << sk::util::String::valueOf(fd);
    }

    sk::util::StringArray& _descriptors;
    DescriptorPropagator _propagator;
  };
}
    
void 
sk::sys::StreamPortal::
importStreams(const sk::util::PropertyRegistry& registry)
{
  descriptors(registry).forEach(StreamImporter(_streams));
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
    streams.forEach(StreamExporter(descriptors));
    registry.setProperty("SK_STREAMS", descriptors.join("|"));
  }
  else {
    descriptors(registry).forEach(DescriptorPropagator());
  }
}

void 
sk::sys::StreamPortal::
clear()
{
  for(int fd=3; fd < 1024; ++fd) {
    sk::io::LooseFileDescriptor descriptor(fd);
    try {
      descriptor.inheritable(false);
    }
    catch(const sk::rt::SystemException& exception) {}
  }
}
