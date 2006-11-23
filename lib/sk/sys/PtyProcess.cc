/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/sys/PtyProcess.h>
#include <sk/io/Pty.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/EOFException.h>

struct sk::sys::PtyProcess::Listener 
  : public virtual sk::sys::ProcessListener 
{
    void processStarting();
    int processStopping();
    void processJoining();

    sk::io::Pty pty;
    sk::util::StringArray errors;
};

sk::sys::PtyProcess::
PtyProcess(const sk::util::StringArray& cmdline)
  : _listenerHolder(new Listener), _process(_listenerHolder.get().pty.getMasterSlavePipe().inputStream(), cmdline, _listenerHolder.get())
{
  _listenerHolder.get().pty.getSlaveMasterPipe().closeOutput();
}

sk::sys::PtyProcess::
~PtyProcess()
{
}

sk::sys::Executable&
sk::sys::PtyProcess::
getExecutable()
{
  return _process;
}

const sk::sys::Executable&
sk::sys::PtyProcess::
getExecutable() const
{
  return _process;
}

const sk::util::Class
sk::sys::PtyProcess::
getClass() const
{
  return sk::util::Class("sk::sys::PtyProcess");
}

sk::io::Pty&
sk::sys::PtyProcess::
getPty()
{
  return _listenerHolder.get().pty;
}

sk::io::InputStream& 
sk::sys::PtyProcess::
inputStream() const
{
  return _listenerHolder.get().pty.getSlaveMasterPipe().inputStream();
}

sk::io::InputStream& 
sk::sys::PtyProcess::
inputErrorStream() const
{
  return _listenerHolder.get().pty.getSlaveMasterPipe().inputStream();
}

sk::io::OutputStream&
sk::sys::PtyProcess::
outputStream() const
{
  return _listenerHolder.get().pty.getMasterSlavePipe().outputStream();
}

const sk::util::StringArray& 
sk::sys::PtyProcess::
errors() const
{
  return _listenerHolder.get().errors;
}

void 
sk::sys::PtyProcess::Listener::
processStarting()
{
  ::close(1);
  ::dup(pty.getSlaveMasterPipe().outputStream().getFileDescriptor().getFileNumber());

  ::close(2);
  ::dup(pty.getSlaveMasterPipe().outputStream().getFileDescriptor().getFileNumber());

  pty.getMasterSlavePipe().closeOutput();
  pty.getSlaveMasterPipe().close();
  pty.closeMaster();
  pty.closeSlave();
}

int 
sk::sys::PtyProcess::Listener::
processStopping()
{
  pty.getMasterSlavePipe().outputStream().close();
  return 1;
}

void 
sk::sys::PtyProcess::Listener::
processJoining()
{
  pty.getMasterSlavePipe().outputStream().close();
}
