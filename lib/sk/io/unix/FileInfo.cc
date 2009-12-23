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

#include "../FileInfoData.h"

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
