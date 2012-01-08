/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/SystemException.h>
#include <sk/io/FileDescriptor.h>

#include "PtySpecifics.h"
#include <stdlib.h>
#include <fcntl.h>

void
sk::io::PtySpecifics::
setup()
{
  int fd = posix_openpt(O_RDWR);
  if(fd < 0) {
    throw sk::util::SystemException("posix_openpt()");
  }
  fd = makeMaster(FileDescriptor(fd));

  if(unlockpt(fd) < 0) {
    throw sk::util::SystemException("unlockpt()");
  }
  if(grantpt(fd) < 0) {
    throw sk::util::SystemException("grantpt()");
  }
  makeSlave(ptsname(fd));
}
