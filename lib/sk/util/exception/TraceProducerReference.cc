/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include "TraceProducerReference.h"

static const sk::util::String __className("sk::util::exception::TraceProducerReference");

sk::util::exception::TraceProducerReference::
TraceProducerReference(sk::util::exception::trace::Producer* producer)
  : _producerHolder(producer), _producer(_producerHolder.getMutable()), 
    _links(0), _traceCollected(false), _resetDone(false)
{
  try {
    _producer.setup();
  }
  catch(const std::exception& exception) {
    setError("setup", exception.what());
  }
  catch(...) {
    setError("setup", "Unknown exception");
  }
}

sk::util::exception::TraceProducerReference::
~TraceProducerReference()
{
  reset();
}

const sk::util::Class
sk::util::exception::TraceProducerReference::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::util::exception::TraceProducerReference::
link()
{
  return ++_links;
}

int
sk::util::exception::TraceProducerReference::
unlink()
{
  return --_links;
}

const sk::util::String&
sk::util::exception::TraceProducerReference::
trace() 
{
  ensureTraceCollected();
  return _trace;
}

const sk::util::String&
sk::util::exception::TraceProducerReference::
traceWithMessage(const sk::util::String& message) 
{
  ensureTraceCollected();
  _buffer = message + "\n" + _trace;

  return _buffer;
}

void
sk::util::exception::TraceProducerReference::
reset()
{
  if(_resetDone == true) {
    return;
  }
  try {
    _producer.reset();
  }
  catch(const std::exception& exception) {
    setError("reset", exception.what());
  }
  catch(...) {
    setError("reset", "Unknown exception");
  }
}

void
sk::util::exception::TraceProducerReference::
ensureTraceCollected()
{
  if(_traceCollected == false) {
    try {
      _trace = _producer.produceTrace();
    }
    catch(const std::exception& exception) {
      setError("produce", exception.what());
    }
    catch(...) {
      setError("produce", "Unknown exception");
    }
    _traceCollected = true;
    reset();
  }
}

void 
sk::util::exception::TraceProducerReference::
setError(const sk::util::String& stage, const sk::util::String& message) 
{
  _traceCollected = true;
  _trace += "<Error in trace " + stage + ": " + message + ">";
}
