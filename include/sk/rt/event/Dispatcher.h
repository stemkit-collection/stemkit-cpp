/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_DISPATCHER_H_
#define _SK_RT_EVENT_DISPATCHER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace event {
      class Dispatcher 
        : public virtual sk::util::Object
      {
        public:
          Dispatcher();
          virtual ~Dispatcher();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Dispatcher(const Dispatcher& other);
          Dispatcher& operator = (const Dispatcher& other);
      };
    }
  }
}

#endif /* _SK_RT_EVENT_DISPATCHER_H_ */
