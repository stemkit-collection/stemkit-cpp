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

#include <sk/io/FileInfo.h>

static const sk::util::String __className("sk::io::FileInfo");

sk::io::FileInfo::
FileInfo()
{
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
