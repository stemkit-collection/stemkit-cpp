/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <logger/StreamDestination.h>

sk::rt::logger::StreamDestination::
StreamDestination(std::ostream& destination)
  : _destination(destination)
{
}

sk::rt::logger::StreamDestination::
~StreamDestination()
{
}

const sk::util::Class
sk::rt::logger::StreamDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::StreamDestination");
}

void
sk::rt::logger::StreamDestination::
makeReady()
{
}

void
sk::rt::logger::StreamDestination::
dispatch(const char* buffer, int size) 
{
  _destination.write(buffer, size);
}

sk::rt::logger::StreamDestination*
sk::rt::logger::StreamDestination::
clone() const
{
  return new StreamDestination(*this);
}
