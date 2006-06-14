/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/ByteArrayOutputStream.h>

sk::io::ByteArrayOutputStream::
ByteArrayOutputStream()
{
}

sk::io::ByteArrayOutputStream::
~ByteArrayOutputStream()
{
}

const sk::util::Class
sk::io::ByteArrayOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::ByteArrayOutputStream");
}
