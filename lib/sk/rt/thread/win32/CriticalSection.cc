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

#include "CriticalSection.h"

static const sk::util::Class __class("sk::rt::thread::win32::CriticalSection");

sk::rt::thread::win32::CriticalSection::
CriticalSection()
{
}

sk::rt::thread::win32::CriticalSection::
~CriticalSection()
{
}

const sk::util::Class
sk::rt::thread::win32::CriticalSection::
getClass() const
{
  return __class;
}
