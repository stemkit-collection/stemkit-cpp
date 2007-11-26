/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/ExternalStreamDestination.h>

sk::rt::logger::ExternalStreamDestination::
ExternalStreamDestination(std::ostream& destination)
  : _destination(destination)
{
}

sk::rt::logger::ExternalStreamDestination::
~ExternalStreamDestination()
{
}

const sk::util::Class
sk::rt::logger::ExternalStreamDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::ExternalStreamDestination");
}

void
sk::rt::logger::ExternalStreamDestination::
dispatch(std::stringstream& stream) 
{
  _destination << stream.rdbuf();
}

sk::rt::logger::ExternalStreamDestination*
sk::rt::logger::ExternalStreamDestination::
clone() const
{
  return new ExternalStreamDestination(*this);
}
