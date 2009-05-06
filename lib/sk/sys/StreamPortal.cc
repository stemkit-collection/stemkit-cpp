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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/sys/StreamPortal.h>

static const char* __className("sk::sys::StreamPortal");

sk::sys::StreamPortal::
StreamPortal()
{
}

sk::sys::StreamPortal::
~StreamPortal()
{
}

const sk::util::Class
sk::sys::StreamPortal::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::sys::StreamPortal::
size() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::Stream& 
sk::sys::StreamPortal::
get(int index) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::StreamPortal::
forEach(const sk::util::Processor<sk::io::Stream>& stream) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
    
