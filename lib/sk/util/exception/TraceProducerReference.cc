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
  : _producerHolder(producer), _links(0)
{
}

sk::util::exception::TraceProducerReference::
~TraceProducerReference()
{
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String&
sk::util::exception::TraceProducerReference::
traceWithMessage(const sk::util::String& message) 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
