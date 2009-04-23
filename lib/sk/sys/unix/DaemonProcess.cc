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
#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/io/NullDevice.h>

#include <sk/sys/DaemonProcess.h>
#include <sk/sys/Process.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/sys/AbstractProcessListener.h>
#include "ManagedProcess.h"

static const char* __className("sk::sys::DaemonProcess");

sk::sys::DaemonProcess::
DaemonProcess(const sk::util::StringArray& cmdline)
  : _scope(__className), _cmdline(cmdline), _detached(false)
{
}

sk::sys::DaemonProcess::
~DaemonProcess()
{
  if(_detached == false && _executableHolder.isEmpty() == false) {
    sk::util::Exception::guard(_scope.warning(SK_METHOD), *this, &sk::sys::DaemonProcess::stop);
  }
}

bool
sk::sys::DaemonProcess::
isAlive() const
{
  if(_executableHolder.isEmpty() == true) {
    return false;
  }
  return _executableHolder.get().isAlive();
}

void
sk::sys::DaemonProcess::
detach()
{
  _detached = true;
}

void 
sk::sys::DaemonProcess::
startDetached()
{
  _detached = true;
  start();
}

void 
sk::sys::DaemonProcess::
start()
{
  if(_executableHolder.isEmpty() == false) {
    throw sk::util::IllegalStateException("Process already started");
  }
  sk::sys::Process process(*this);
  _pipe.outputStream().close();
  sk::io::DataInputStream stream(_pipe.inputStream());

  int pid = stream.readInt();
  process.join();

  _pipe.inputStream().close();
  _executableHolder.set(new ManagedProcess(pid));
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
  if(_executableHolder.isEmpty() == true) {
    throw sk::util::IllegalStateException("Process not started");
  }
  return _executableHolder.get();
}

const sk::sys::Executable& 
sk::sys::DaemonProcess::
getExecutable() const
{
  if(_executableHolder.isEmpty() == true) {
    throw sk::util::IllegalStateException("Process not started");
  }
  return _executableHolder.get();
}

namespace {
  struct FileDescriptorSweeper : public sk::sys::AbstractProcessListener {
    void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
      sk::io::NullDevice trash;

      configurator.setInputStream(trash.inputStream());
      configurator.setOutputStream(trash.outputStream());
      configurator.setErrorOutputStream(trash.outputStream());
    }
  };
}

void 
sk::sys::DaemonProcess::
processStarting() 
{
  ::setsid();

  FileDescriptorSweeper sweeper;
  sk::sys::Process process(_cmdline, sweeper);
  _pipe.inputStream().close();
  sk::io::DataOutputStream stream(_pipe.outputStream());
  stream.writeInt(process.getPid());
  stream.close();
  process.detach();
}

int 
sk::sys::DaemonProcess::
processStopping() 
{
  return 0;
}

void 
sk::sys::DaemonProcess::
processJoining() 
{
}

void 
sk::sys::DaemonProcess::
processConfiguring(sk::sys::ProcessConfigurator& configurator)
{
}
