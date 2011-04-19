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
Exception(const sk::util::String& message)
  : _message(join("ERROR", message))
{
}

sk::util::Exception::
Exception(const sk::util::String& message, sk::util::Exception& exception)
  : _message(join(join("ERROR", message), exception.getMessage()))
{
}

sk::util::Exception::
Exception(const sk::util::String& message, const std::exception& exception)
  : _message(join(join("ERROR", message), exception.what()))
{
}

sk::util::Exception::
Exception(const sk::util::String& message, const sk::util::Strings& strings)
  : _message(join(join("ERROR", message), strings.join(":")))
{
}

sk::util::Exception::
~Exception() throw()
{
}

const sk::util::String
sk::util::Exception::
getMessage() const
{
  return _message.substring(_message.indexOf(' ') + 1);
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

const char*
sk::util::Exception::
what() const throw()
{
  return _message.getChars();
}

const sk::util::String
sk::util::Exception::
join(const sk::util::String& s1, const sk::util::String& s2) const
{
  return s1 + ": " + s2;
}

const sk::util::String
sk::util::Exception::
join(const sk::util::String& s1, int i1) const
{
  return join(s1, sk::util::Integer::toString(i1));
}
