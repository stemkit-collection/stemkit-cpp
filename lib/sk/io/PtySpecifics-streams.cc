/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sys/stropts.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/StringArray.h>
#include <sk/util/Processor.h>
#include <sk/util/SystemException.h>
#include <sk/io/File.h>

#include "PtySpecifics.h"

namespace {
  struct ModulePusher : public virtual sk::util::Processor<const sk::util::String> {
    ModulePusher(int fd) 
      : _fd(fd) {}

    void process(const sk::util::String& module) const {
      if(ioctl(_fd, I_PUSH, module.getChars()) < 0) {
        throw sk::util::SystemException(sk::util::String("ioctl(") + sk::util::Integer::toString(_fd) + ", I_PUSH, " + module.inspect() + ")");
      }
    }
    int _fd;
  };
}

void
sk::io::PtySpecifics::
setup()
{
  int fd = makeMaster(sk::io::File("/dev/ptmx", "r+").getFileDescriptor());

  if(unlockpt(fd) < 0) {
    throw sk::util::SystemException("unlockpt()");
  }
  if(grantpt(fd) < 0) {
    throw sk::util::SystemException("grantpt()");
  }
  sk::util::StringArray modules = sk::util::StringArray("ptem") + "ldterm" + "ttcompat";
  modules.forEach(ModulePusher(makeSlave(ptsname(fd))));
}
