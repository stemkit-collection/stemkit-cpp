/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "Main.h"

sk::rt::thread::Main::
Main()
{
}

sk::rt::thread::Main::
~Main()
{
}

const sk::util::Class
sk::rt::thread::Main::
getClass() const
{
  return sk::util::Class("sk::rt::thread::Main");
}
