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
#include <sk/util/Holder.cxx>
#include <sk/util/MappingProcessor.cxx>
#include <sk/util/SelectingProcessor.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/io/ClosedChannelException.h>
#include <sk/rt/SystemException.h>
#include <sk/io/mapper/PathnameToFileInfo.h>
#include <sk/io/selector/Directory.h>
#include <sk/io/selector/RegularFile.h>

#include <sk/io/Dir.h>
#include <sk/io/FileInfo.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>

static const sk::util::String __className("sk::io::Dir");

sk::io::Dir::
Dir(const sk::util::Pathname& path)
  : _path(path)
{
  init();
}

sk::io::Dir::
~Dir()
{
  close();
}

const sk::util::Class
sk::io::Dir::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::Pathname& 
sk::io::Dir::
getPath() const
{
  return _path;
}

void 
sk::io::Dir::
forEachEntry(const sk::util::Processor<const sk::io::FileInfo>& processor) const
{
  forEachEntry(sk::util::MappingProcessor<const sk::util::Pathname, const sk::io::FileInfo>(processor, sk::io::mapper::PathnameToFileInfo()));
}

void 
sk::io::Dir::
forEachDirectory(const sk::util::Processor<const sk::io::FileInfo>& processor) const
{
  forEachEntry(sk::util::SelectingProcessor<const sk::io::FileInfo>(processor, sk::io::selector::Directory()));
}

void 
sk::io::Dir::
forEachRegularFile(const sk::util::Processor<const sk::io::FileInfo>& processor) const
{
  forEachEntry(sk::util::SelectingProcessor<const sk::io::FileInfo>(processor, sk::io::selector::RegularFile()));
}

