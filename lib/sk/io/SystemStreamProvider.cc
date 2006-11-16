/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/AbstractPipe.h>
#include <sk/io/FileDescriptorInputStream.h>

#include "SystemStreamProvider.h"

sk::io::SystemStreamProvider::
SystemStreamProvider()
{
  initStdin();
  initStdout();
  initStderr();
}

sk::io::SystemStreamProvider::
~SystemStreamProvider()
{
}

const sk::util::Class
sk::io::SystemStreamProvider::
getClass() const
{
  return sk::util::Class("sk::io::SystemStreamProvider");
}

sk::io::Pipe&
sk::io::SystemStreamProvider::
getStdin() const
{
  return _stdinHolder.get();
}

sk::io::Pipe&
sk::io::SystemStreamProvider::
getStdout() const
{
  return _stdoutHolder.get();
}

sk::io::Pipe&
sk::io::SystemStreamProvider::
getStderr() const
{
  return _stderrHolder.get();
}

namespace {
  struct StdinPipe : public sk::io::AbstractPipe {
    StdinPipe() 
      : _stream(0) {}

    void closeInput() {
      _stream.close();
    }
    sk::io::InputStream& inputStream() const {
      return _stream;
    }
    mutable sk::io::FileDescriptorInputStream _stream;
  };
}

void
sk::io::SystemStreamProvider::
initStdin()
{
  _stdinHolder.set(new StdinPipe);
}
