/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/TrashDisposer.h>

sk::sys::TrashDisposer::
TrashDisposer()
{
}

sk::sys::TrashDisposer::
~TrashDisposer()
{
}

const sk::util::Class
sk::sys::TrashDisposer::
getClass() const
{
  return sk::util::Class("sk::sys::TrashDisposer");
}
