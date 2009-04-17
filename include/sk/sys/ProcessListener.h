/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_PROCESSLISTENER_
#define _SK_SYS_PROCESSLISTENER_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class ProcessConfigurator;

    class ProcessListener
      : public virtual sk::util::Object 
    {
      public:
        virtual void processStarting() = 0;
        virtual int processStopping() = 0;
        virtual void processJoining() = 0;
        virtual void processConfiguring(sk::sys::ProcessConfigurator& configurator) = 0;
    };
  }
}

#endif /* _SK_SYS_PROCESSLISTENER_ */
