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
#include <sk/util/Integer.h>
#include <sk/io/LooseFileDescriptor.h>

#include "../StreamPortalPropagator.h"

static const char* __className("sk::sys::StreamPortalPropagator");

const sk::util::Class
sk::sys::StreamPortalPropagator::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::sys::StreamPortalPropagator::
process(const sk::util::String& descriptor) const 
{
  propagate(sk::util::Integer::parseInt(descriptor));
}

int 
sk::sys::StreamPortalPropagator::
propagate(int fd) const 
{
  sk::io::LooseFileDescriptor descriptor(fd);
  descriptor.inheritable(true);

  return fd;
}

