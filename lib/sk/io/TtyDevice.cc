/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/TtyDevice.h>

sk::io::TtyDevice::
TtyDevice(const sk::util::String& name)
  : sk::io::File(name, "r+")
{
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

const sk::util::String
sk::io::TtyDevice::
getName() const
{
  return sk::io::File::getName();
}

void
sk::io::TtyDevice::
setLines(int lines)
{
  // TODO: Provide actual implementation, ignoring the call for now.
  // throw sk::util::UnsupportedOperationException("setLines()");
}

void 
sk::io::TtyDevice::
setColumns(int columns)
{
  // TODO: Provide actual implementation, ignoring the call for now.
  // throw sk::util::UnsupportedOperationException("setColumns()");
}
