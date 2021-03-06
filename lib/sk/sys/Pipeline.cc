/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/Pipeline.h>

sk::sys::Pipeline::
Pipeline()
{
}

sk::sys::Pipeline::
~Pipeline()
{
}

const sk::util::Class
sk::sys::Pipeline::
getClass() const
{
  return sk::util::Class("sk::sys::Pipeline");
}
