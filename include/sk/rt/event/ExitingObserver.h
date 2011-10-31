/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_EXITINGOBSERVER_H_
#define _SK_RT_EVENT_EXITINGOBSERVER_H_

#include <sk/rt/event/Observer.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    namespace event {
      class ExitingObserver 
        : public virtual sk::rt::event::Observer
      {
        public:
          ExitingObserver(const int code);
          virtual ~ExitingObserver();

          // sk::rt::event::Observer implementation.
          bool processEvent(const sk::rt::Event& event);
      
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

#endif /* _SK_RT_EVENT_EXITINGOBSERVER_H_ */
