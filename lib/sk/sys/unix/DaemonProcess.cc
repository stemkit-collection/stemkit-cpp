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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/sys/DaemonProcess.h>

static const char* __className("sk::sys::DaemonProcess");

sk::sys::DaemonProcess::
DaemonProcess(const sk::util::StringArray& cmdline)
  : _scope(__className), _cmdline(cmdline)
{
}

sk::sys::DaemonProcess::
~DaemonProcess()
{
}

void 
sk::sys::DaemonProcess::
start()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::Class
sk::sys::DaemonProcess::
getClass() const
{
  return sk::util::Class(__className);
}

sk::sys::Executable& 
sk::sys::DaemonProcess::
getExecutable()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::sys::Executable& 
sk::sys::DaemonProcess::
getExecutable() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::DaemonProcess::
processStarting() 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::sys::DaemonProcess::
processStopping() 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::DaemonProcess::
processJoining() 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
