/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/String.h>

#include <sk/rt/StackTracerFactory.h>
#include "StackTracer.h"

sk::util::exception::trace::Producer*
sk::rt::StackTracerFactory::
createTraceProducer() const 
{
  return new StackTracer();
}
