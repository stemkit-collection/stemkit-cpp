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
#include <sk/io/File.h>

#include <sk/sys/DaemonProcess.h>
#include <sk/sys/Process.h>
#include "ManagedProcess.h"

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
  for(int fd=0; fd<256 ;fd++) {
    ::close(fd);
  }
  sk::io::File trash("/dev/null", "r+");
  ::dup(trash.getFileDescriptor().getFileNumber());
  ::dup(trash.getFileDescriptor().getFileNumber());

  ::setsid();

  sk::sys::Process process(_cmdline);
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::DaemonProcess::
processJoining() 
{
}
