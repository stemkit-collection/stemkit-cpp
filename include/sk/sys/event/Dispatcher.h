/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_SYS_EVENT_DISPATCHER_H_
#define _SK_SYS_EVENT_DISPATCHER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class Event;

    namespace event {
      class Observer;

      class Dispatcher 
        : public virtual sk::util::Object
      {
        public:
          Dispatcher();
          virtual ~Dispatcher();

          void addEventObserver(const sk::sys::Event& event, const sk::sys::event::Observer& observer);
          void removeEventObserver(const sk::sys::Event& event, const sk::sys::event::Observer& observer);
          void removeEventObservers(const sk::sys::Event& event);
          void removeEventsObserver(const sk::sys::event::Observer& observer);
          void clear();

          void listenAndDispatch();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Dispatcher(const Dispatcher& other);
          Dispatcher& operator = (const Dispatcher& other);
      };
    }
  }
}

#endif /* _SK_SYS_EVENT_DISPATCHER_H_ */
