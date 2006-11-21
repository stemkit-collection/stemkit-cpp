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
#include <sk/io/File.h>

#include "PtyImpl.h"

sk::io::Pty::
Pty()
  : _implHolder(new PtyImpl), _inputStream(_implHolder.get().getSlave()), _outputStream(_implHolder.get().getMaster())
{
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
  closeInput();
  closeOutput();
}


void 
sk::io::Pty::
closeInput()
{
  _inputStream.close();
  _implHolder.get().getSlave().close();
}

void 
sk::io::Pty::
closeOutput()
{
  _outputStream.close();
  _implHolder.get().getMaster().close();
}

sk::io::FileDescriptorInputStream& 
sk::io::Pty::
inputStream() const
{
  return _inputStream;
}

sk::io::FileDescriptorOutputStream& 
sk::io::Pty::
outputStream() const
{
  return _outputStream;
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
