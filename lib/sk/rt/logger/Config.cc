/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Config.h>

sk::rt::logger::Config::
Config()
{
}

sk::rt::logger::Config::
~Config()
{
}

const sk::util::Class
sk::rt::logger::Config::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Config");
}
