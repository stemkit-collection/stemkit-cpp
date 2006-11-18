/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/sys/PipeProcess.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/io/FileDescriptorOutputStream.h>

class sk::sys::PipeProcess::Listener 
  : public virtual sk::sys::ProcessListener 
{
  public:
    void processStarting();
    int processStopping();
    void processJoining();

    sk::io::AnonymousPipe stdinPipe;
    sk::io::AnonymousPipe stdoutPipe;
    sk::io::AnonymousPipe stderrPipe;
};

sk::sys::PipeProcess::
PipeProcess(const sk::util::StringArray& cmdline)
  : DelegatingExecutable(_process), _listenerHolder(new Listener), 
    _process(_listenerHolder.get().stdinPipe.inputStream(), cmdline, _listenerHolder.get())
{
}

sk::sys::PipeProcess::
~PipeProcess()
{
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

sk::io::OutputStream&
sk::sys::PipeProcess::
outputStream() const
{
  return _listenerHolder.get().stdinPipe.outputStream();
}

void 
sk::sys::PipeProcess::Listener::
processStarting()
{
  ::close(1);
  ::dup(stdoutPipe.outputStream().getFileDescriptor().getFileNumber());

  ::close(2);
  ::dup(stderrPipe.outputStream().getFileDescriptor().getFileNumber());
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
  /*
  sk::io::DataInputStream stream(_ownStreamProviderHolder.get().getStderr().inputStream());
  try {
    while(true) {
      _errors << stream.readLine();
    }
  }
  catch(const sk::io::EOFException& exception) {}
  */
}
