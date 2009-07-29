/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Holder.cxx>
#include <sk/rt/ProcessInfo.h>
#include <sk/util/IllegalStateException.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/task.h>
#include <mach/mach_init.h>

// The actual solution is borrowed from here:
//   http://miknight.blogspot.com/2005/11/resident-set-size-in-mac-os-x.html
//
// Thanks to Michael Knight for posting it.
//
struct sk::rt::ProcessInfo::Data 
{
  Data(pid_t pid) : _task(MACH_PORT_NULL) {
    if (task_for_pid(current_task(), pid, &_task) != KERN_SUCCESS) {
      throw sk::util::IllegalStateException("Mac OS X task");
    }
  }

  const struct task_basic_info info()
  {
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    task_info(_task, TASK_BASIC_INFO, task_info_t(&t_info), &t_info_count);
    return t_info;
  }

  private:
    task_t _task;
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
  return virtualMemory();
}

uint64_t
sk::rt::ProcessInfo::
virtualMemory() const
{
  return _dataHolder.get().info().virtual_size;
}

uint64_t
sk::rt::ProcessInfo::
residentMemory(sk::rt::Lock& lock) const
{
  return residentMemory();
}

uint64_t
sk::rt::ProcessInfo::
residentMemory() const
{
  return _dataHolder.get().info().resident_size;
}
