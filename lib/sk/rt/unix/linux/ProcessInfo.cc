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
#include <sk/util/Strings.h>
#include <sk/rt/ProcessInfo.h>
#include <sk/rt/Locker.h>

struct sk::rt::ProcessInfo::Data 
  : sk::util::Object
{
  Data(pid_t pid) 
    : _statfile("/proc/" + sk::util::String::valueOf(pid) + "/stat") {}

  uint64_t numericEntryAt(int index) {
    sk::util::File file(_statfile);
    return sk::util::Integer::parseInt(file.getLine().split().get(index));
  }

  private:
    sk::util::String _statfile;
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
  return _dataHolder.getMutable().numericEntryAt(22);
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
  return _dataHolder.getMutable().numericEntryAt(23);
}
