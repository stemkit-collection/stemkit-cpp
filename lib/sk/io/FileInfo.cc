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
#include <sk/util/MissingResourceException.h>

#include <sk/io/FileInfo.h>
#include <sk/rt/SystemException.h>
#include <sys/stat.h>
#include <time.h>

static const sk::util::String __className("sk::io::FileInfo");

struct sk::io::FileInfo::Data : public virtual sk::util::Object {
  struct stat status;
};


sk::io::FileInfo::
FileInfo(const sk::util::String& path)
  : _path(path.trim()), _dataHolder(new Data)
{
  if(::stat(_path.getChars(), &_dataHolder.get().status) != 0) {
    throw sk::rt::SystemException("stat()");
  }
}

sk::io::FileInfo::
FileInfo(int descriptor)
  : _dataHolder(new Data)
{
  if(::fstat(descriptor, &_dataHolder.get().status) != 0) {
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

const sk::util::String& 
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

bool
sk::io::FileInfo::
isSymlink() const
{
  return _dataHolder.get().status.st_mode & S_IFLNK;
}

bool
sk::io::FileInfo::
isSocket() const
{
  return _dataHolder.get().status.st_mode & S_IFSOCK;
}

bool
sk::io::FileInfo::
isPipe() const
{
  return _dataHolder.get().status.st_mode & S_IFIFO;
}

bool
sk::io::FileInfo::
isDevice() const
{
  return _dataHolder.get().status.st_mode & (S_IFCHR | S_IFBLK);
}

namespace {
  uint64_t figureTime(const struct timespec spec) {
    return (spec.tv_sec * 1000000) + (spec.tv_nsec / 1000);
  }
}

uint64_t
sk::io::FileInfo::
getTimeUpdated() const
{
  return figureTime(_dataHolder.get().status.st_ctimespec);
}

uint64_t
sk::io::FileInfo::
getTimeModified() const
{
  return figureTime(_dataHolder.get().status.st_mtimespec);
}

uint64_t
sk::io::FileInfo::
getTimeAccessed() const
{
  return figureTime(_dataHolder.get().status.st_atimespec);
}
