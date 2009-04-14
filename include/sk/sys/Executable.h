/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_EXECUTABLE_
#define _SK_SYS_EXECUTABLE_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class Executable
      : public virtual sk::util::Object 
    {
      public:
        virtual void stop() = 0;
        virtual void join() = 0;
        virtual void detach() = 0;
        virtual bool isSuccess() const = 0;
        virtual bool isExited() const = 0;
        virtual bool isKilled() const = 0;
        virtual bool isAlive() const = 0;
        virtual int exitStatus() const = 0;
        virtual int signal() const = 0;
        virtual int getPid() const = 0;
    };
  }
}

#endif /* _SK_SYS_EXECUTABLE_ */
