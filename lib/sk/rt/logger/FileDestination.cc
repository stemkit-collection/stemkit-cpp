/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/NumberFormatException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/logger/FileDestination.h>

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname)
  : _pathname(pathname), _size(0), _chunks(0)
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
  throw sk::util::UnsupportedOperationException("dispatch()");
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
