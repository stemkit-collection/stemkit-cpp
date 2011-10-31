/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_OBSERVER_H_
#define _SK_RT_EVENT_OBSERVER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    class Event;

    namespace event {
      class Observer 
        : public virtual sk::util::Object
      {
        public:
          virtual bool processEvent(const sk::rt::Event& event) = 0;
      };
    }
  }
}

#endif /* _SK_RT_EVENT_OBSERVER_H_ */
