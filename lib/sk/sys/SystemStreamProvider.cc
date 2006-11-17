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
#include <sk/io/FileDescriptorOutputStream.h>

#include "SystemStreamProvider.h"

namespace {
  struct InputPipe : public sk::io::AbstractPipe {
    InputPipe(int fd) 
      : _stream(fd) {}

    void closeInput() {
      _stream.close();
    }
    sk::io::FileDescriptorInputStream& inputStream() const {
      return _stream;
    }
    mutable sk::io::FileDescriptorInputStream _stream;
  };

  struct OutputPipe : public sk::io::AbstractPipe {
    OutputPipe(int fd) 
      : _stream(fd) {}

    void closeOutput() {
      _stream.close();
    }
    sk::io::FileDescriptorOutputStream& outputStream() const {
      return _stream;
    }
    mutable sk::io::FileDescriptorOutputStream _stream;
  };
}

sk::io::SystemStreamProvider::
SystemStreamProvider()
{
  _stdinHolder.set(new InputPipe(dup(0)));
  _stdoutHolder.set(new OutputPipe(dup(1)));
  _stderrHolder.set(new OutputPipe(dup(2)));
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

