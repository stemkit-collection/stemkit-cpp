/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/TtyDevice.h>

sk::io::TtyDevice::
TtyDevice(const sk::util::String& name)
  : sk::io::File(name, "r+")
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::TtyDevice::
~TtyDevice()
{
}

const sk::util::Class
sk::io::TtyDevice::
getClass() const
{
  return sk::util::Class("sk::io::TtyDevice");
}

sk::io::TtyFileDescriptor&
sk::io::TtyDevice::
getFileDescriptor() const
{
  return _descriptorHolder.getMutable();
}

sk::io::Tty& 
sk::io::TtyDevice::
getTty() 
{
  return _descriptorHolder.getMutable();
}

const sk::io::Tty& 
sk::io::TtyDevice::
getTty() const
{
  return _descriptorHolder.get();
}

void
sk::io::TtyDevice::
close()
{
  sk::io::File::close();
  _descriptorHolder.getMutable().close();
}
