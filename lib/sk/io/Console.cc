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

#include <sk/io/Console.h>

static const char* __className("sk::io::Console");

sk::io::Console::
Console()
  : sk::io::File("/dev/tty", "r+")
{
}

sk::io::Console::
~Console()
{
}

const sk::util::Class
sk::io::Console::
getClass() const
{
  return sk::util::Class(__className);
}
