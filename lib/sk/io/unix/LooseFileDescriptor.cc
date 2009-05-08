/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/LooseFileDescriptor.h>
#include <sk/rt/SystemException.h>
#include <unistd.h>
#include <fcntl.h>

void 
sk::io::LooseFileDescriptor::
inheritable(bool state)
{
  int fd = getFileNumber();
  int flags = fcntl(fd, F_GETFD);
  if(flags == -1) {
    throw sk::rt::SystemException("fcntl:F_GETFD");
  }
  if(state == false) {
    flags |= FD_CLOEXEC;
  }
  else {
    flags &= ~(FD_CLOEXEC);
  }
  if(fcntl(fd, F_SETFD, flags) == -1) {
    throw sk::rt::SystemException("fcntl:F_SETFD");
  }
}

