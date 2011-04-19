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
#include <sk/util/Strings.h>

#include <sk/rt/thread/Exit.h>

static const char* __className("sk::rt::thread::Exit");

sk::rt::thread::Exit::
Exit(int code)
  : Exception(sk::util::Strings("Thread exit") << sk::util::String::valueOf(code)), _code(code)
{
}

sk::rt::thread::Exit::
~Exit() throw()
{
}

const sk::util::Class
sk::rt::thread::Exit::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::rt::thread::Exit::
getCode() const
{
  return _code;
}
