/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "../FileInfoData.h"

bool
sk::io::FileInfo::
isSymlink() const
{
  return false;
}

bool
sk::io::FileInfo::
isSocket() const
{
  return false;
}

bool
sk::io::FileInfo::
isPipe() const
{
  return false;
}

bool
sk::io::FileInfo::
isDevice() const
{
  return false;
}
