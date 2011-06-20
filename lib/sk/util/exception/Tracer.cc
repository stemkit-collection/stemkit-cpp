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
#include <sk/util/Holder.cxx>
#include <sk/util/exception/trace/ProducerFactory.h>

#include "TraceProducerReference.h"

namespace {
  sk::util::Holder<sk::util::exception::trace::ProducerFactory>::Direct __factoryHolder;
}

void 
sk::util::exception::Tracer::
setProducerFactory(const sk::util::exception::trace::ProducerFactory& factory)
{
  __factoryHolder.set(sk::util::covariant<sk::util::exception::trace::ProducerFactory>(factory.clone()));
}

void 
sk::util::exception::Tracer::
clearProducerFactory()
{
  __factoryHolder.clear();
}

sk::util::exception::Tracer::
Tracer()
  : _reference(__factoryHolder.isEmpty() ? 0 : new TraceProducerReference(__factoryHolder.get().createTraceProducer()))
{
  if(_reference != 0) {
    _reference->link();
  }
}

sk::util::exception::Tracer::
Tracer(const sk::util::exception::Tracer& other)
  : _reference(other._reference)
{
  if(_reference != 0) {
    _reference->link();
  }
}

sk::util::exception::Tracer::
~Tracer()
{
  if(_reference != 0) {
    if(_reference->unlink() == 0) {
      delete _reference;
    }
  }
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
