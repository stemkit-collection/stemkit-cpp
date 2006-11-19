/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/sys/PipeProcess.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/EOFException.h>

struct sk::sys::PipeProcess::Listener 
  : public virtual sk::sys::ProcessListener 
{
    void processStarting();
    int processStopping();
    void processJoining();

    sk::io::AnonymousPipe stdinPipe;
    sk::io::AnonymousPipe stdoutPipe;
    sk::io::AnonymousPipe stderrPipe;

    sk::util::StringArray errors;
};

sk::sys::PipeProcess::
PipeProcess(const sk::util::StringArray& cmdline)
  : _listenerHolder(new Listener), _process(_listenerHolder.get().stdinPipe.inputStream(), cmdline, _listenerHolder.get())
{
  _listenerHolder.get().stdoutPipe.closeOutput();
  _listenerHolder.get().stderrPipe.closeOutput();
}

sk::sys::PipeProcess::
~PipeProcess()
{
}

sk::sys::Executable&
sk::sys::PipeProcess::
getExecutable()
{
  return _process;
}

const sk::sys::Executable&
sk::sys::PipeProcess::
getExecutable() const
{
  return _process;
}

const sk::util::Class
sk::sys::PipeProcess::
getClass() const
{
  return sk::util::Class("sk::sys::PipeProcess");
}

sk::io::InputStream& 
sk::sys::PipeProcess::
inputStream() const
{
  return _listenerHolder.get().stdoutPipe.inputStream();
}

sk::io::InputStream& 
sk::sys::PipeProcess::
inputErrorStream() const
{
  return _listenerHolder.get().stderrPipe.inputStream();
}

sk::io::OutputStream&
sk::sys::PipeProcess::
outputStream() const
{
  return _listenerHolder.get().stdinPipe.outputStream();
}

const sk::util::StringArray& 
sk::sys::PipeProcess::
errors() const
{
  return _listenerHolder.get().errors;
}

void 
sk::sys::PipeProcess::Listener::
processStarting()
{
  ::close(1);
  ::dup(stdoutPipe.outputStream().getFileDescriptor().getFileNumber());

  ::close(2);
  ::dup(stderrPipe.outputStream().getFileDescriptor().getFileNumber());

  stdinPipe.closeOutput();
  stdoutPipe.close();
  stderrPipe.close();
}

int 
sk::sys::PipeProcess::Listener::
processStopping()
{
  stdinPipe.outputStream().close();
  return 1;
}

void 
sk::sys::PipeProcess::Listener::
processJoining()
{
  stdinPipe.outputStream().close();

  sk::io::DataInputStream stream(stderrPipe.inputStream());
  try {
    while(true) {
      errors << stream.readLine();
    }
  }
  catch(const sk::io::EOFException& exception) {}
}
