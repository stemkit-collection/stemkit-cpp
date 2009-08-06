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
#include <sk/rt/ProcessInfo.h>
#include <sk/util/UnsupportedOperationException.h>

#include <windows.h>
#include <psapi.h>

void 
sk::rt::ProcessInfo::
init()
{
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
  PROCESS_MEMORY_COUNTERS_EX info = { 0 };
  info.cb = sizeof(info);

  if(GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&info), sizeof(info)) == TRUE) {
    // return info.PagefileUsage;
    return info.PrivateUsage;
  }
  return 0;
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
  PROCESS_MEMORY_COUNTERS_EX info = { 0 };
  info.cb = sizeof(info);

  if(GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&info), sizeof(info)) == TRUE) {
    return info.WorkingSetSize;
  }
  return 0;
}
