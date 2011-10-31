/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_SYS_EVENT_EXITINGOBSERVER_H_
#define _SK_SYS_EVENT_EXITINGOBSERVER_H_

#include <sk/sys/event/Observer.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace sys {
    namespace event {
      class ExitingObserver 
        : public virtual sk::sys::event::Observer
      {
        public:
          ExitingObserver(const int code);
          virtual ~ExitingObserver();

          // sk::sys::event::Observer implementation.
          bool processEvent(const sk::sys::Event& event);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ExitingObserver& operator = (const ExitingObserver& other);

          const int _code;
          const sk::rt::Scope _scope;
      };
    }
  }
}

#endif /* _SK_SYS_EVENT_EXITINGOBSERVER_H_ */
