/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_MANAGEDPROCESS_H_
#define _SK_SYS_MANAGEDPROCESS_H_

#include <sk/util/Object.h>
#include <sk/sys/Executable.h>

namespace sk {
  namespace sys {
    class ManagedProcess 
      : public virtual sk::sys::Executable
    {
      public:
        ManagedProcess(pid_t pid);
        virtual ~ManagedProcess();
    
        // sk::sys::Executable implementation.
        void stop();
        void join();
        void detach();
        bool isSuccess() const;
        bool isExited() const;
        bool isKilled() const;
        bool isAlive() const;
        int exitStatus() const;
        int signal() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        ManagedProcess(const ManagedProcess& other);
        ManagedProcess& operator = (const ManagedProcess& other);

        pid_t _pid;
    };
  }
}

#endif /* _SK_SYS_MANAGEDPROCESS_H_ */
