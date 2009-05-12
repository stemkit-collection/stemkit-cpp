/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/rt/SystemException.h>
#include <sk/io/LooseFileDescriptor.h>
#include <sk/sys/StreamPortal.h>

#include <winnutc.h>

void 
sk::sys::StreamPortal::
clear()
{
  for(int fd=3; fd < 1024; ++fd) {
    sk::io::LooseFileDescriptor descriptor(fd);
    try {
      descriptor.inheritable(false);
    }
    catch(const sk::rt::SystemException& exception) {}
    ::SetHandleInformation(::_NutFdToHandle(fd), HANDLE_FLAG_INHERIT, 0);
  }
}
