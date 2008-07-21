/*  vim: set sw=2:
 *
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include "PipeDestination.h"

sk::rt::logger::PipeDestination::
PipeDestination(const logger::Destination& destination)
  : _destinationHolder(destination.clone()), _descriptor(-1), _piped(false)
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination");
}

sk::rt::logger::PipeDestination::
PipeDestination(const PipeDestination& other)
  : _destinationHolder(other._destinationHolder), _descriptor(other.cloneDescriptor()), _piped(other._piped)
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination");
}

sk::rt::logger::PipeDestination::
~PipeDestination()
{
}

void 
sk::rt::logger::PipeDestination::
cleanup()
{
}

const sk::util::Class
sk::rt::logger::PipeDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::PipeDestination");
}

sk::rt::logger::PipeDestination*
sk::rt::logger::PipeDestination::
clone() const
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::clone()");
}

int 
sk::rt::logger::PipeDestination::
cloneDescriptor() const
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::cloneDescriptor()");
}

const std::vector<int>
sk::rt::logger::PipeDestination::
makeReady()
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::makeReady()");
}

void
sk::rt::logger::PipeDestination::
dispatch(const char* buffer, int size)
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::dispatch()");
}

void
sk::rt::logger::PipeDestination::
close()
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::close()");
}

bool
sk::rt::logger::PipeDestination::
makePipe()
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::makePipe()");
}

void
sk::rt::logger::PipeDestination::
output(const sk::util::String& message)
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::output()");
}

void
sk::rt::logger::PipeDestination::
waitData(int descriptor)
{
  throw sk::util::UnsupportedOperationException("sk::rt::logger::PipeDestination::waitData()");
}
