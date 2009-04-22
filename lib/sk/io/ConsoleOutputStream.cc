/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/ConsoleOutputStream.h>

static const char* __className("sk::io::ConsoleOutputStream");

sk::io::ConsoleOutputStream::
ConsoleOutputStream()
  : sk::io::FileOutputStream("/dev/tty")
{
}

sk::io::ConsoleOutputStream::
~ConsoleOutputStream()
{
}

const sk::util::Class
sk::io::ConsoleOutputStream::
getClass() const
{
  return sk::util::Class(__className);
}
