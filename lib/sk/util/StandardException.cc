/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/util/StandardException.h>

sk::util::StandardException::
StandardException(const sk::util::String& label, const std::exception& exception)
  : sk::util::Exception(sk::util::Strings(label) << exception.what())
{
}

sk::util::StandardException::
StandardException(const std::exception& exception)
  : sk::util::Exception(exception.what())
{
}

const sk::util::Class
sk::util::StandardException::
getClass() const
{
  return sk::util::Class("std::exception");
}
