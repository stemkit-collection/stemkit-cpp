/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/Exception.h>

sk::util::Exception::
Exception(const sk::util::String& message)
  : _message(message)
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
  return join("ERROR", _message);
}

const sk::util::Class
sk::util::Exception::
getClass() const
{
  return sk::util::Class("sk::util::Exception");
}

const char*
sk::util::Exception::
what() const throw()
{
  return getMessage().getChars();
}

const sk::util::String
sk::util::Exception::
join(const sk::util::String& s1, const sk::util::String& s2) const
{
  return s1 + ':' + s2;
}
