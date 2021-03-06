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
#include <sk/io/FileInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/TtyFileDescriptor.h>

#include "PtyImpl.h"
#include <sk/io/AbstractFileDescriptorPipe.h>

namespace {
  struct FileDescriptorPipe : public sk::io::AbstractFileDescriptorPipe {
    FileDescriptorPipe(const sk::io::FileDescriptor& output, const sk::io::FileDescriptor& input) {
      setOutputFileDescriptor(output);
      setInputFileDescriptor(input);
    }
  };
}

sk::io::Pty::
Pty()
  : _scope(*this)
{
  PtyImpl pty;
  pty.setup();

  _masterSlavePipeHolder.set(new FileDescriptorPipe(pty.getMaster(), pty.getSlave()));
  _slaveMasterPipeHolder.set(new FileDescriptorPipe(pty.getSlave(), pty.getMaster()));
  _ttyHolder.set(new TtyFileDescriptor(pty.getSlave()));

  _name = pty.getName();

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

const sk::util::String
sk::io::Pty::
getName() const
{
  return _name;
}

void
sk::io::Pty::
close()
{
  closeTty();

  _masterSlavePipeHolder.getMutable().close();
  _slaveMasterPipeHolder.getMutable().close();
}

void
sk::io::Pty::
closeTty()
{
  _ttyHolder.getMutable().close();
}

sk::io::Tty&
sk::io::Pty::
getTty()
{
  return _ttyHolder.getMutable();
}

const sk::io::Tty&
sk::io::Pty::
getTty() const
{
  return _ttyHolder.get();
}

sk::io::FileDescriptorPipe&
sk::io::Pty::
getMasterSlavePipe()
{
  return _masterSlavePipeHolder.getMutable();
}

sk::io::FileDescriptorPipe&
sk::io::Pty::
getSlaveMasterPipe()
{
  return _slaveMasterPipeHolder.getMutable();
}
