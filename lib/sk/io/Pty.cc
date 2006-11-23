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

#include <sk/io/Pty.h>
#include <sk/io/TtyDevice.h>
#include <sk/io/FileInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

#include "PtyImpl.h"
#include <sk/io/AbstractPipe.h>

namespace {
  struct FileDescriptorPipe : public sk::io::AbstractPipe {
    FileDescriptorPipe(const sk::io::FileDescriptor& output, const sk::io::FileDescriptor& input) {
      setOutputFileDescriptor(output);
      setInputFileDescriptor(input);
    }
  };
}

sk::io::Pty::
Pty()
  : _implHolder(new PtyImpl)
{
  _implHolder.get().setup();

  const sk::io::FileDescriptor& masterFileDescriptor = _implHolder.get().getMaster();
  const sk::io::FileDescriptor& slaveFileDescriptor = _implHolder.get().getSlave().getFileDescriptor();

  _masterSlavePipeHolder.set(new FileDescriptorPipe(masterFileDescriptor, slaveFileDescriptor));
  _slaveMasterPipeHolder.set(new FileDescriptorPipe(slaveFileDescriptor, masterFileDescriptor));

  setLines(24);
  setColumns(80);
}

sk::io::Pty::
~Pty()
{
}

const sk::util::Class
sk::io::Pty::
getClass() const
{
  return sk::util::Class("sk::io::Pty");
}

void 
sk::io::Pty::
close()
{
  closeMaster();
  closeSlave();

  _masterSlavePipeHolder.get().close();
  _slaveMasterPipeHolder.get().close();
}

void
sk::io::Pty::
closeMaster()
{
  _implHolder.get().getMaster().close();
}

void
sk::io::Pty::
closeSlave()
{
  _implHolder.get().getSlave().close();
}

sk::io::Tty& 
sk::io::Pty::
getTty()
{
  return _implHolder.get().getTty();
}

const sk::io::Tty& 
sk::io::Pty::
getTty() const
{
  return _implHolder.get().getTty();
}

sk::io::Pipe& 
sk::io::Pty::
getMasterSlavePipe()
{
  return _masterSlavePipeHolder.get();
}

sk::io::Pipe& 
sk::io::Pty::
getSlaveMasterPipe()
{
  return _slaveMasterPipeHolder.get();
}
