/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/logger/FileDestination.h>

sk::rt::logger::FileDestination::
FileDestination()
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

void
sk::rt::logger::FileDestination::
dispatch(std::stringstream& stream)
{
  throw sk::util::UnsupportedOperationException("dispatch()");
}
