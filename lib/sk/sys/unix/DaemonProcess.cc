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
#include <sk/sys/ProcessListener.h>

static const char* __className("sk::sys::DaemonProcess");

struct sk::sys::DaemonProcess::Listener : public virtual sk::sys::ProcessListener {
  Listener(const sk::util::StringArray& cmdline) 
    : _cmdline(cmdline) {}

  void processStarting() {
    throw sk::util::UnsupportedOperationException(__FUNCTION__);
  }
  int processStopping() {
    throw sk::util::UnsupportedOperationException(__FUNCTION__);
  }
  void processJoining() {
    throw sk::util::UnsupportedOperationException(__FUNCTION__);
  }

  const sk::util::StringArray _cmdline;
};

sk::sys::DaemonProcess::
DaemonProcess(const sk::util::StringArray& cmdline)
  : _scope(__className), _listenerHolder(new Listener(cmdline))
{
}

sk::sys::DaemonProcess::
~DaemonProcess()
{
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
