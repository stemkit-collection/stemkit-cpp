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

#include <sk/util/Holder.cxx>

namespace {
  sk::util::Holder<sk::util::trace::ProducerFactory>::Direct __factoryHolder;
}

void 
sk::util::Tracer::
setProducerFactory(const sk::util::trace::ProducerFactory& factory)
{
  __factoryHolder.set(sk::util::covariant<sk::util::trace::ProducerFactory>(factory.clone()));
}

void 
sk::util::Tracer::
clearProducerFactory()
{
  __factoryHolder.clear();
}

sk::util::Tracer::
Tracer()
  : _reference(__factoryHolder.isEmpty() ? 0 : new trace::ProducerReference(__factoryHolder.get().createTraceProducer()))
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
finalize() const
{
  if(_reference != 0) {
    _reference->finalize();
  }
}
