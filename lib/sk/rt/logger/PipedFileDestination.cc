/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/logger/PipedFileDestination.h>

sk::rt::logger::PipedFileDestination::
PipedFileDestination(const sk::util::Pathname& pathname)
  : FileDestination(pathname)
{
}

sk::rt::logger::PipedFileDestination::
~PipedFileDestination()
{
}

const sk::util::Class
sk::rt::logger::PipedFileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::PipedFileDestination");
}

sk::rt::logger::PipedFileDestination*
sk::rt::logger::PipedFileDestination::
clone() const
{
  return new PipedFileDestination(*this);
}

void
sk::rt::logger::PipedFileDestination::
dispatch(std::stringstream& stream)
{
  throw sk::util::UnsupportedOperationException("dispatch()");
}
