/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_H_
#define _SK_RT_EVENT_H_

#include <sk/util/Object.h>
#include <sk/rt/event/content.h>

namespace sk {
  namespace rt {
    class Event 
      : public virtual sk::util::Object
    {
      public:
        Event();
        virtual ~Event();

        static void setup();
        static void reset();
        static sk::rt::event::Dispatcher& dispatcher();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Event(const Event& other);
        Event& operator = (const Event& other);
    };
  }
}

#endif /* _SK_RT_EVENT_H_ */
