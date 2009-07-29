/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/File.h>
#include <sk/util/StringArray.h>
#include <sk/rt/ProcessInfo.h>
#include <sk/rt/Locker.h>

namespace {
  uint64_t get_stat_at(const sk::util::String& statfile, int index) {
    sk::util::File file(statfile);
    return sk::util::Integer::parseInt(sk::util::StringArray::parse(file.getLine()).get(index));
  }
}

struct sk::rt::ProcessInfo::Data {
  Data(pid_t pid) 
    : statfile("/proc/" + sk::util::String::valueOf(pid) + "/stat") {}

  sk::util::String statfile;
};

void
sk::rt::ProcessInfo::
init()
{
  _dataHolder.set(new Data(_pid));
}

uint64_t
sk::rt::ProcessInfo::
virtualMemory(sk::rt::Lock& lock) const
{
  sk::rt::Locker locker(lock);
  return virtualMemory();
}

uint64_t
sk::rt::ProcessInfo::
virtualMemory() const
{
  return get_stat_at(_dataHolder.get().statfile, 22);
}

uint64_t
sk::rt::ProcessInfo::
residentMemory(sk::rt::Lock& lock) const
{
  sk::rt::Locker locker(lock);
  return residentMemory();
}

uint64_t
sk::rt::ProcessInfo::
residentMemory() const
{
  return get_stat_at(_dataHolder.get().statfile, 23);
}
