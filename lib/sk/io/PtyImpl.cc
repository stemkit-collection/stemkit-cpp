/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/io/File.h>

#include "PtyImpl.h"

sk::io::PtyImpl::
PtyImpl()
  : _logger(*this)
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

int 
sk::io::PtyImpl::
makeMaster(const sk::io::FileDescriptor& descriptor)
{
  return _masterHolder.set(new sk::io::FileDescriptor(descriptor)).get().getFileNumber();
}

int
sk::io::PtyImpl::
makeSlave(const sk::util::String& name)
{
  _name = name;
  return _slaveHolder.set(new sk::io::FileDescriptor(File(name, "r+").getFileDescriptor())).get().getFileNumber();
}

const sk::util::String
sk::io::PtyImpl::
getName() const
{
  return _name;
}

sk::io::FileDescriptor& 
sk::io::PtyImpl::
getMaster()
{
  return _masterHolder.get();
}

sk::io::FileDescriptor&
sk::io::PtyImpl::
getSlave()
{
  return _slaveHolder.get();
}
