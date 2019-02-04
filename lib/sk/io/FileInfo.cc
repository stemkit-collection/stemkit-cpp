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
#include <sk/util/StringArray.h>
#include <sk/util/MissingResourceException.h>

#include <sk/io/FileInfo.h>
#include <sk/rt/SystemException.h>
#include <time.h>

static const sk::util::String __className("sk::io::FileInfo");

#include "FileInfoData.h"

sk::io::FileInfo::
FileInfo(const sk::util::Pathname& path)
  : _path(path), _dataHolder(new Data)
{
  if(::stat(_path.toString().getChars(), &_dataHolder.getMutable().status) != 0) {
    throw sk::rt::SystemException("stat()");
  }
}

sk::io::FileInfo::
FileInfo(int descriptor)
  : _dataHolder(new Data), _path("")
{
  if(::fstat(descriptor, &_dataHolder.getMutable().status) != 0) {
    throw sk::rt::SystemException("fstat()");
  }
}

sk::io::FileInfo::
~FileInfo()
{
}

const sk::util::Class
sk::io::FileInfo::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::Pathname& 
sk::io::FileInfo::
getPath() const 
{
  if(_path.isEmpty() == false) {
    return _path;
  }
  throw sk::util::MissingResourceException("file path");
}

uint64_t
sk::io::FileInfo::
getSize() const
{
  return _dataHolder.get().status.st_size;
}
 
bool
sk::io::FileInfo::
isDirectory() const
{
  return _dataHolder.get().status.st_mode & S_IFDIR;
}

bool
sk::io::FileInfo::
isRegular() const
{
  return _dataHolder.get().status.st_mode & S_IFREG;
}

namespace {
  const sk::rt::Time figureTime(time_t moment) {
    return sk::rt::Time::at(moment);
  }
}

const sk::rt::Time
sk::io::FileInfo::
getTimeUpdated() const
{
  return figureTime(_dataHolder.get().status.st_ctime);
}

const sk::rt::Time
sk::io::FileInfo::
getTimeModified() const
{
  return figureTime(_dataHolder.get().status.st_mtime);
}

const sk::rt::Time
sk::io::FileInfo::
getTimeAccessed() const
{
  return figureTime(_dataHolder.get().status.st_atime);
}

const sk::util::String
sk::io::FileInfo::
getType() const
{
  if(isDirectory() == true) {
    return "directory";
  }
  if(isRegular() == true) {
    return "file";
  }
  if(isSymlink() == true) {
    return "symlink";
  }
  if(isSocket() == true) {
    return "socket";
  }
  if(isPipe() == true) {
    return "pipe";
  }
  if(isDevice() == true) {
    return "device";
  }
  return "unknown";
}

const sk::util::String
sk::io::FileInfo::
inspect() const
{
  sk::util::StringArray depot;

  depot << getType() + '=' + _path.inspect();
  {
    std::stringstream stream;
    stream << getSize();
    depot << "size=" + stream.str();
  }
  depot << "accessed_at=" + getTimeAccessed().inspect();
  depot << "modified_at=" + getTimeModified().inspect();
  depot << "updated_at=" + getTimeUpdated().inspect();
  
  return "<FileInfo: " + depot.join(", ") + '>';
}
