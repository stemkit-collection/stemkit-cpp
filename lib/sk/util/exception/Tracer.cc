/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/exception/Tracer.h>
#include "TraceProducerReference.h"

sk::util::exception::Tracer::
Tracer()
  : _reference(0)
{
}

sk::util::exception::Tracer::
Tracer(const sk::util::exception::Tracer& other)
  : _reference(0)
{
}

sk::util::exception::Tracer::
~Tracer()
{
}

const sk::util::String&
sk::util::exception::Tracer::
trace() const
{
  if(_reference == 0) {
    return sk::util::String::EMPTY;
  }
  return _reference->trace();
}

const sk::util::String&
sk::util::exception::Tracer::
traceWithMessage(const sk::util::String& message) const
{
  if(_reference == 0) {
    return message;
  }
  return _reference->traceWithMessage(message);
}
