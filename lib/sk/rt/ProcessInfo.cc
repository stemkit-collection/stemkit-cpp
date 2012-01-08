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
#include <sk/util/Holder.cxx>

#include <sk/rt/ProcessInfo.h>
#include <unistd.h>

static const char* __className("sk::rt::ProcessInfo");

namespace {
  sk::util::Holder<sk::rt::ProcessInfo> __currentInfoHolder;
  bool setup = (sk::rt::ProcessInfo::reset(), true);
}

sk::rt::ProcessInfo::
ProcessInfo()
  : _pid(getpid())
{
  init();
}

sk::rt::ProcessInfo::
~ProcessInfo()
{
}

const sk::util::Class
sk::rt::ProcessInfo::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::ProcessInfo::
reset()
{
  __currentInfoHolder.set(new sk::rt::ProcessInfo());
}

const sk::rt::ProcessInfo&
sk::rt::ProcessInfo::
current()
{
  return __currentInfoHolder.get();
}

uint64_t
sk::rt::ProcessInfo::
pid() const
{
  return _pid;
}
