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

#include <sk/sys/StreamPortal.h>
#include <sk/rt/Environment.h>
#include <sk/io/FileDescriptorInputStream.h>

static const char* __className("sk::sys::StreamPortal");

sk::sys::StreamPortal::
StreamPortal()
{
  populate(sk::util::StringArray::parse(sk::rt::Environment().getProperty("SK_STREAMS", ""), "|"));
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
    FileDescriptorStreamMaker(sk::util::ArrayList<sk::io::Stream>& depot)
      : _depot(depot) {}

    void process(const sk::util::String& item) const {
      int fd = sk::util::Integer::parseInt(item);
      _depot.add(new sk::io::FileDescriptorInputStream(fd));
    }

    sk::util::ArrayList<sk::io::Stream>& _depot;
  };
}
    
void 
sk::sys::StreamPortal::
populate(const sk::util::StringArray& ids)
{
  ids.forEach(FileDescriptorStreamMaker(_streams));
}
