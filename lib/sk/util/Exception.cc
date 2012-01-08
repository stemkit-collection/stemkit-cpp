/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>

#include <sk/util/Exception.h>
#include <sk/util/Strings.h>
#include <sk/util/Holder.cxx>
#include <sk/util/trace/ProducerFactory.h>

#include <stdlib.h>

namespace {
  struct NullProducerFactory : public virtual sk::util::trace::ProducerFactory {
    sk::util::trace::Producer* createTraceProducer() const {
      return 0;
    }
  };
  sk::util::Holder<sk::util::trace::ProducerFactory>::Direct __factoryHolder(new NullProducerFactory);
}

void
sk::util::Exception::
setTraceProducerFactory(const sk::util::trace::ProducerFactory& factory)
{
  __factoryHolder.set(sk::util::covariant<sk::util::trace::ProducerFactory>(factory.clone()));
}

void
sk::util::Exception::
clearTraceProducerFactory()
{
  __factoryHolder.set(new NullProducerFactory);
}

sk::util::Exception::
Exception(const sk::util::Strings& strings)
  : _message(strings.join(": ")), _tracer(__factoryHolder.get())
{
}

sk::util::Exception::
Exception(const sk::util::Strings& strings, const sk::util::Exception& exception)
  : _message((strings + exception.getMessage()).join(": ")), _tracer(exception._tracer)
{
}

const sk::util::String
sk::util::Exception::
getMessage() const
{
  return _message;
}

sk::util::Exception::
~Exception() throw()
{
}

const sk::util::Class
sk::util::Exception::
getClass() const
{
  return sk::util::Class("sk::util::Exception");
}

const sk::util::String
sk::util::Exception::
inspect() const
{
  return getClass().getName() + "[" + getMessage() + "]";
}

const sk::util::String
sk::util::Exception::
getTrace() const
{
  return _tracer.trace();
}

int
sk::util::Exception::
defaultExitCode() const
{
  return 4;
}

void
sk::util::Exception::
exit() const
{
  exit(defaultExitCode());
}

void
sk::util::Exception::
finalize() const
{
  _tracer.finalizeFor("exception");
}

void
sk::util::Exception::
exit(int code) const
{
  finalize();
  ::exit(code);
}

const char*
sk::util::Exception::
what() const throw()
{
  return _tracer.traceWithMessage(_message).getChars();
}
