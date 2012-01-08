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
#include <sk/io/File.h>

static const sk::util::String __className("sk::io::Console");

struct sk::io::Console::Data : public virtual sk::util::Object {
  Data()
    : file("/dev/tty", "r+") {}

  sk::io::File file;
};

sk::io::Console::
Console()
  : _dataHolder(new Data()), _data(_dataHolder.getMutable())
{
}

sk::io::Console::
~Console()
{
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
  _data.file.close();
}

sk::io::InputStream&
sk::io::Console::
inputStream() const
{
  return _data.file.inputStream();
}

sk::io::OutputStream&
sk::io::Console::
outputStream() const
{
  return _data.file.outputStream();
}
