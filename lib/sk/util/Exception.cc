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

sk::util::Exception::
Exception(const sk::util::Strings& strings)
  : _message(strings.join(": "))
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

const char*
sk::util::Exception::
what() const throw()
{
  return _tracer.traceWithMessage(_message).getChars();
}
