/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/io/TtyDevice.h>

#include "PtyImpl.h"

sk::io::PtyImpl::
PtyImpl()
  : _master("/dev/ptmx", "r+")
{
  setup(_master.getFileDescriptor().getFileNumber());
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
  return _deviceHolder.get();
}

const sk::io::Tty&
sk::io::PtyImpl::
getTty()  const
{
  return _deviceHolder.get();
}

int
sk::io::PtyImpl::
makeSlave(const sk::util::String& name)
{
  return _deviceHolder.set(new TtyDevice(name)).get().getFileDescriptor().getFileNumber();
}

sk::io::File& 
sk::io::PtyImpl::
getMaster()
{
  return _master;
}

sk::io::TtyDevice&
sk::io::PtyImpl::
getSlave()
{
  return _deviceHolder.get();
}
