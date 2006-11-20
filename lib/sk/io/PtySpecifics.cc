/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "PtySpecifics.h"

sk::io::PtySpecifics::
PtySpecifics()
{
}

sk::io::PtySpecifics::
~PtySpecifics()
{
}

const sk::util::Class
sk::io::PtySpecifics::
getClass() const
{
  return sk::util::Class("sk::io::PtySpecifics");
}

void
sk::io::PtySpecifics::
setup()
{
  int fd = _master.getFileDescriptor().getFileNumber();

  if(unlockpt(fd) < 0) {
    throw sk::util::SystemException("unlockpt()");
  }
  grantpt(fd);

  sk::io::TtyDevice(ptsname(fd), "w+", O_RDWR | O_NOCTTY);
}
