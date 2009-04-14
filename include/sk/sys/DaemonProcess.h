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
#include <sk/util/StringArray.h>
#include <sk/sys/Process.h>

namespace sk {
  namespace sys {
    class DaemonProcess 
      : public virtual sk::util::Object
    {
      public:
        DaemonProcess(const sk::util::StringArray& cmdline);
        virtual ~DaemonProcess();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        DaemonProcess(const DaemonProcess& other);
        DaemonProcess& operator = (const DaemonProcess& other);

        struct Listener;

        const sk::rt::Scope _scope;
        sk::util::Holder<Listener> _listenerHolder;
        sk::sys::Process _process;
    };
  }
}

#endif /* _SK_SYS_DAEMONPROCESS_H_ */
