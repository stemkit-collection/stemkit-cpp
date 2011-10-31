/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_LOGGINGOBSERVER_H_
#define _SK_RT_EVENT_LOGGINGOBSERVER_H_

#include <sk/rt/event/Observer.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    namespace event {
      class LoggingObserver 
        : public virtual sk::rt::event::Observer
      {
        public:
          LoggingObserver(const sk::rt::Scope& scope);
          virtual ~LoggingObserver();
      
          // sk::rt::event::Observer implementation.
          bool processEvent(const sk::rt::Event& event);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          LoggingObserver& operator = (const LoggingObserver& other);
          const sk::rt::Scope& _scope;
      };
    }
  }
}

#endif /* _SK_RT_EVENT_LOGGINGOBSERVER_H_ */
