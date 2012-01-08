/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

struct sk::sys::PtyProcess::Listener
  : public sk::sys::AbstractProcessListener
{
};

sk::sys::PtyProcess::
PtyProcess(const sk::util::Strings& cmdline)
  : _scope(*this),
    _listenerHolder(new Listener), _process(getPty().getMasterSlavePipe().inputStream(), cmdline, _listenerHolder.getMutable())
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::InputStream&
sk::sys::PtyProcess::
inputStream() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::InputStream&
sk::sys::PtyProcess::
inputErrorStream() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::OutputStream&
sk::sys::PtyProcess::
outputStream() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::Strings&
sk::sys::PtyProcess::
errors() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

