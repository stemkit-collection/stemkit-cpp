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
#include <sk/util/StringArray.h>

#include <sk/sys/StreamPortal.h>
#include <sk/io/FileDescriptorInputStream.h>

static const char* __className("sk::sys::StreamPortal");

sk::sys::StreamPortal::
StreamPortal(const sk::util::PropertyRegistry& registry)
{
  populateFrom(registry);
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
  struct FileDescriptorStreamMaker : public virtual sk::util::Processor<const sk::util::String> {
    FileDescriptorStreamMaker(sk::util::ArrayList<sk::io::Stream>& streams)
      : _streams(streams) {}

    void process(const sk::util::String& item) const {
      int fd = sk::util::Integer::parseInt(item);
      _streams.add(new sk::io::FileDescriptorInputStream(fd));
    }

    sk::util::ArrayList<sk::io::Stream>& _streams;
  };

  struct StreamPropagator : public virtual sk::util::Processor<const sk::io::Stream> {
    StreamPropagator(sk::util::StringArray& items)
      : _items(items) {}

    void process(const sk::io::Stream& stream) const {
      sk::io::LooseFileDescriptor descriptor = sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor();
      descriptor.inheritable(true);
      _items << sk::util::String::valueOf(descriptor.getFileNumber());
    }

    sk::util::StringArray& _items;
  };
}
    
void 
sk::sys::StreamPortal::
populateFrom(const sk::util::PropertyRegistry& registry)
{
  sk::util::StringArray items = sk::util::StringArray::parse(registry.getProperty("SK_STREAMS", ""), "|");
  items.forEach(FileDescriptorStreamMaker(_streams));
}

void 
sk::sys::StreamPortal::
exportStreams(const sk::util::List<const sk::io::Stream>& streams, sk::util::PropertyRegistry& registry)
{
  sk::util::StringArray items;
  streams.forEach(StreamPropagator(items));

  if(items.isEmpty() == false) {
    registry.setProperty("SK_STREAMS", items.join("|"));
  }
}
