/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_DELEGATINGEXECUTABLE_
#define _SK_SYS_DELEGATINGEXECUTABLE_

#include <sk/sys/Executable.h>

namespace sk {
  namespace sys {
    class DelegatingExecutable
      : public virtual sk::sys::Executable
    {
      public:
        DelegatingExecutable(sk::sys::Executable& executable);
        virtual ~DelegatingExecutable();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::sys::Executable implementation.
        void stop();
        void join();
        bool isSuccess() const;
        bool isExited() const;
        bool isKilled() const;
        bool isAlive() const;
        int exitStatus() const;
        int signal() const;

      private:
        DelegatingExecutable(const DelegatingExecutable& other);
        DelegatingExecutable& operator = (const DelegatingExecutable& other);

        sk::sys::Executable& _executable;
    };
  }
}

#endif /* _SK_SYS_DELEGATINGEXECUTABLE_ */
