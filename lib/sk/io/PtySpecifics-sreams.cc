/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sys/stropts.h>

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

namespace {
  struct ModulePusher : public virtual sk::util::Processor<const sk::util::String> {
    ModulePusher(int fd) 
      : _fd(fd) {}

    void process(const sk::util::String& module) const {
      if(ioctl(_fd, I_PUSH, module.getChars()) < 0) {
        throw sk::util::SystemException("ioctl(" + _fd + ", I_PUSH, " + module.inspect() + ")");
      }
    }
    int _fd;
  };
}

void
sk::io::PtySpecifics::
setup(int fd)
{
  if(unlockpt(fd) < 0) {
    throw sk::util::SystemException("unlockpt()");
  }
  if(grantpt(fd) < 0) {
    throw sk::util::SystemException("grantpt()");
  }
  int fd = makeSlave(ptsname(fd));

  sk::util::StringArray modules = sk::uitl::StringArray("ptem") + "ldterm" + "ttcompat";
  modules.forEach(ModulePusher(fd));
}
