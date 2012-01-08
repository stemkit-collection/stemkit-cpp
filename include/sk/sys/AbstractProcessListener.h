/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_ABSTRACTPROCESSLISTENER_
#define _SK_SYS_ABSTRACTPROCESSLISTENER_

#include <sk/sys/ProcessListener.h>

namespace sk {
  namespace sys {
    class AbstractProcessListener
      : public virtual sk::sys::ProcessListener
    {
      public:
        virtual ~AbstractProcessListener();

        void processStarting(sk::io::Stream& umbilical);
        void processStopping();
        void processJoining();
        void processFailing(const sk::util::String& message);
        void processConfiguring(sk::sys::ProcessConfigurator& configurator);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        AbstractProcessListener();

      private:
        AbstractProcessListener(const AbstractProcessListener& other);
        AbstractProcessListener& operator = (const AbstractProcessListener& other);
    };
  }
}

#endif /* _SK_SYS_ABSTRACTPROCESSLISTENER_ */
