/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <logger/TrashDestination.h>

sk::rt::logger::TrashDestination::
TrashDestination()
{
}

sk::rt::logger::TrashDestination::
~TrashDestination()
{
}

const sk::util::Class
sk::rt::logger::TrashDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::TrashDestination");
}

const std::vector<int>
sk::rt::logger::TrashDestination::
makeReady()
{
  return std::vector<int>();
}

void
sk::rt::logger::TrashDestination::
dispatch(const char* /*buffer*/, int /*size*/)
{
}

sk::util::Object*
sk::rt::logger::TrashDestination::
clone() const
{
  return new TrashDestination(*this);
}
