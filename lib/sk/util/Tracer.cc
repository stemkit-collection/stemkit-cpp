/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Tracer.h>
#include <sk/util/trace/ProducerFactory.h>
#include "trace/ProducerReference.h"

namespace {
  sk::util::trace::ProducerReference* makeProducerReference(sk::util::trace::Producer* producer) {
    if(producer == 0) {
      return 0;
    }
    return new sk::util::trace::ProducerReference(producer);
  }
}

sk::util::Tracer::
Tracer(const sk::util::trace::ProducerFactory& factory)
  : _reference(makeProducerReference(factory.createTraceProducer()))
{
  if(_reference != 0) {
    _reference->link();
  }
}

sk::util::Tracer::
Tracer(const sk::util::Tracer& other)
  : _reference(other._reference)
{
  if(_reference != 0) {
    _reference->link();
  }
}

sk::util::Tracer::
~Tracer()
{
  if(_reference != 0) {
    if(_reference->unlink() == 0) {
      delete _reference;
    }
  }
}

const sk::util::String&
sk::util::Tracer::
trace() const
{
  if(_reference == 0) {
    return sk::util::String::EMPTY;
  }
  return _reference->trace();
}

const sk::util::String&
sk::util::Tracer::
traceWithMessage(const sk::util::String& message) const
{
  if(_reference == 0) {
    return message;
  }
  return _reference->traceWithMessage(message);
}

void 
sk::util::Tracer::
finalizeFor(const sk::util::String& scope) const
{
  if(_reference != 0) {
    _reference->finalizeFor(scope);
  }
}
