/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_DAEMONPROCESS_H_
#define _SK_SYS_DAEMONPROCESS_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/util/StringArray.h>
#include <sk/sys/DelegatingExecutable.h>
#include <sk/sys/ProcessListener.h>
#include <sk/io/AnonymousPipe.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace sys {
    class DaemonProcess 
      : public sk::sys::DelegatingExecutable,
        public virtual sk::sys::ProcessListener
    {
      public:
        DaemonProcess(const sk::util::StringArray& cmdline);
        virtual ~DaemonProcess();

        void start();
        void startDetached();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
        // sk::sys::DelegatingExecutable re-implementation.
        bool isAlive() const;
        void detach();

      protected:
        // sk::sys::DelegatingExecutable implementation.
        sk::sys::Executable& getExecutable();
        const sk::sys::Executable& getExecutable() const;

        // sk::sys::ProcessListener implementation.
        void processStarting(sk::io::Stream& umbilical);
        int processStopping();
        void processJoining();
        void processFailing(const sk::util::String& message);
        void processConfiguring(sk::sys::ProcessConfigurator& configurator);

      private:
        DaemonProcess(const DaemonProcess& other);
        DaemonProcess& operator = (const DaemonProcess& other);

        const sk::rt::Scope _scope;
        sk::util::Holder<sk::sys::Executable>  _executableHolder;
        const sk::util::StringArray _cmdline;
        sk::io::AnonymousPipe _pipe;
        bool _detached;
    };
  }
}

#endif /* _SK_SYS_DAEMONPROCESS_H_ */
