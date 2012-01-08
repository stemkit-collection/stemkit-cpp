/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/Console.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

#include <windows.h>
#include <io.h>
#include <fcntl.h>

static const sk::util::String __className("sk::io::Console");

struct sk::io::Console::Data : public virtual sk::util::Object {
  sk::util::Holder<sk::io::InputStream> inputStreamHolder;
  sk::util::Holder<sk::io::OutputStream> outputStreamHolder;
};

sk::io::Console::
Console()
  : _dataHolder(new Data()), _data(_dataHolder.getMutable())
{
  AllocConsole();

  _data.inputStreamHolder.set(new sk::io::FileDescriptorInputStream(_open_osfhandle(DWORD(GetStdHandle(STD_INPUT_HANDLE)), _O_TEXT)));
  _data.outputStreamHolder.set(new sk::io::FileDescriptorOutputStream(_open_osfhandle(DWORD(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT)));
}

sk::io::Console::
~Console()
{
  close();
}

const sk::util::Class
sk::io::Console::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::io::Console::
close()
{
  _data.inputStreamHolder.clear();
  _data.outputStreamHolder.clear();
}

sk::io::InputStream&
sk::io::Console::
inputStream() const
{
  return _data.inputStreamHolder.getMutable();
}

sk::io::OutputStream&
sk::io::Console::
outputStream() const
{
  return _data.outputStreamHolder.getMutable();
}
