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
#include <sk/sys/AbstractProcessListener.h>
#include <sk/sys/ProcessConfigurator.h>
#include <sk/io/Pty.h>
#include <sk/io/File.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/EOFException.h>

#include <unistd.h>

struct sk::sys::PtyProcess::Listener 
  : public sk::sys::AbstractProcessListener 
{
    void processConfiguring(sk::sys::ProcessConfigurator& configurator);
    void processStopping();
    void processJoining();

    sk::io::Pty pty;
    sk::util::Strings errors;
};

sk::sys::PtyProcess::
PtyProcess(const sk::util::Strings& cmdline)
  : _scope(*this),
    _listenerHolder(new Listener), _process(getPty().getMasterSlavePipe().inputStream(), cmdline, _listenerHolder.get())
{
  getPty().getSlaveMasterPipe().closeOutput();
  getPty().closeTty();
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
  const sk::rt::Scope scope = _scope.scope(__FUNCTION__);
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

const sk::util::Strings& 
sk::sys::PtyProcess::
errors() const
{
  return _listenerHolder.get().errors;
}

void 
sk::sys::PtyProcess::Listener::
processConfiguring(sk::sys::ProcessConfigurator& configurator)
{
  setsid();
  
  sk::io::File ctty(pty.getName(), "r+");
  configurator.setInputStream(ctty.inputStream());
  configurator.setOutputStream(ctty.outputStream());
  configurator.setErrorOutputStream(ctty.outputStream());

  pty.close();
}

void
sk::sys::PtyProcess::Listener::
processStopping()
{
  pty.getMasterSlavePipe().outputStream().close();
}

void 
sk::sys::PtyProcess::Listener::
processJoining()
{
  pty.getMasterSlavePipe().outputStream().close();
}
