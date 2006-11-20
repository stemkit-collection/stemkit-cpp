/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include "PtyImpl.h"

sk::io::PtyImpl::
PtyImpl()
{
}

sk::io::PtyImpl::
~PtyImpl()
{
}

const sk::util::Class
sk::io::PtyImpl::
getClass() const
{
  return sk::util::Class("sk::io::PtyImpl");
}

sk::io::Tty&
sk::io::PtyImpl::
getTty() 
{
  return _ttyHolder.get();
}

const sk::io::Tty&
sk::io::PtyImpl::
getTty()  const
{
  return _ttyHolder.get();
}
