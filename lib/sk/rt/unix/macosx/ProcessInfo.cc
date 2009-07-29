/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/rt/ProcessInfo.h>
#include <sk/util/IllegalStateException.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/task.h>
#include <mach/mach_init.h>

namespace {
  // The actual solution is borrowed from here:
  //   http://miknight.blogspot.com/2005/11/resident-set-size-in-mac-os-x.html
  //
  // Thanks to Michael Knight for posting it.
  //
  const struct task_basic_info sk_figure_task_info(task_t task)
  {
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    task_info(task, TASK_BASIC_INFO, task_info_t(&t_info), &t_info_count);
    return t_info;
  }

  task_t sk_figure_task(pid_t pid)
  {
    task_t task = MACH_PORT_NULL;

    if (task_for_pid(current_task(), pid, &task) != KERN_SUCCESS) {
      throw sk::util::IllegalStateException("Mac OS X task");
    }
    return task;
  }
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
  const struct task_basic_info info = sk_figure_task_info(sk_figure_task(_pid));
  return info.virtual_size;
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
  const struct task_basic_info info = sk_figure_task_info(sk_figure_task(_pid));
  return info.resident_size;
}
