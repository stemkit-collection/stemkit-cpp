/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/NumberFormatException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/logger/FileDestination.h>

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname)
  : _pathname(pathname), _size(0), _chunks(0), _bytesWritten(0), _fileHolder(new std::fstream)
{
}

sk::rt::logger::FileDestination::
~FileDestination()
{
}

const sk::util::Class
sk::rt::logger::FileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::FileDestination");
}

sk::rt::logger::FileDestination*
sk::rt::logger::FileDestination::
clone() const
{
  return new FileDestination(*this);
}

void
sk::rt::logger::FileDestination::
dispatch(std::stringstream& stream)
{
  if(_bytesWritten == 0) {
    openFile();
  }
  _fileHolder.get() << stream.rdbuf();
  
  if(_size > 0) {
    _bytesWritten += stream.str().size();
    if(_bytesWritten > _size) {
      _bytesWritten = 0;
      renameFile();
      initFile();
    }
  }
  else {
    _bytesWritten = 1;
  }
}

void
sk::rt::logger::FileDestination::
setSize(const sk::util::String& specification)
{
  try {
    _size = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
setChunks(const sk::util::String& specification)
{
  try {
    _chunks = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
openFile()
{
}

void
sk::rt::logger::FileDestination::
renameFile()
{
}

void
sk::rt::logger::FileDestination::
initFile()
{
}
