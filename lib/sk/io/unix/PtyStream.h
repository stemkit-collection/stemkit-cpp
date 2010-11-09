/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTYSTREAM_
#define _SK_IO_PTYSTREAM_

#include <sk/util/Object.h>
#include "PtySpecifics.h"

#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/SystemException.h>
#include <sk/io/File.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/stropts.h>

namespace sk {
  namespace io {
    class PtyStream
      : public virtual sk::util::Object 
    {
      public:
        PtyStream(sk::io::PtySpecifics& specifics) {
          int fd = specifics.makeMaster(sk::io::File("/dev/ptmx", "r+").getFileDescriptor());

          if(unlockpt(fd) < 0) {
            throw sk::util::SystemException("unlockpt()");
          }
          if(grantpt(fd) < 0) {
            throw sk::util::SystemException("grantpt()");
          }
          _fd = specifics.makeSlave(ptsname(fd));
        }
        
        void push(const sk::util::String& module) {
          if(ioctl(_fd, I_PUSH, module.getChars()) < 0) {
            throw sk::util::SystemException(sk::util::String("ioctl(") + sk::util::Integer::toString(_fd) + ", I_PUSH, " + module.inspect() + ")");
          }
        }

      private:
        int _fd;
    };
  }
}

#endif /* _SK_IO_PTYSTREAM_ */
