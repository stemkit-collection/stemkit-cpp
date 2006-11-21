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

void
sk::io::PtySpecifics::
setup(int fd)
{
  if(unlockpt(fd) < 0) {
    throw sk::util::SystemException("unlockpt()");
  }
  grantpt(fd);

  makeSlave(ptsname(fd));
}
