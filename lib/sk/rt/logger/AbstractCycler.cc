/*  vi: set sw=2:
 *
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/NumberFormatException.h>

#include "AbstractCycler.h"

sk::rt::logger::AbstractCycler::
AbstractCycler(const sk::util::Pathname& masterPathname)
  : _masterPathname(masterPathname), _size(2048), _chunks(3), _bytesWritten(0)
{
}

sk::rt::logger::AbstractCycler::
~AbstractCycler()
{
}

const sk::util::Class
sk::rt::logger::AbstractCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::AbstractCycler");
}

const sk::util::Pathname&
sk::rt::logger::AbstractCycler::
getMasterPathname() const
{ 
  return _masterPathname;
}

int
sk::rt::logger::AbstractCycler::
getSize() const
{
  return _size;
}

void
sk::rt::logger::AbstractCycler::
setSize(const sk::util::String& specification)
{
  try {
    _size = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::AbstractCycler::
setSize(int size)
{
  _size = size;
}

int 
sk::rt::logger::AbstractCycler::
getChunks() const
{
  return _chunks;
}

void
sk::rt::logger::AbstractCycler::
setChunks(const sk::util::String& specification)
{
  try {
    _chunks = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::AbstractCycler::
setChunks(int chunks)
{
  _chunks = chunks;
}

off_t
sk::rt::logger::AbstractCycler::
offset() const
{
  return _bytesWritten;
}

bool
sk::rt::logger::AbstractCycler::
advance(off_t size)
{
  if(getSize() > 0) {
    _bytesWritten += size;
    if(_bytesWritten > getSize()) {
      cycleFile();
      initFile();

      _bytesWritten = 0;
      return false;
    }
  }
  else {
    _bytesWritten = 1;
  }
  return true;
}

