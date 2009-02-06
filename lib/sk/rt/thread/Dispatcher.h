/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_DISPATCHER_H_
#define _SK_RT_THREAD_DISPATCHER_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/thread/Mutex.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Dispatcher 
        : public virtual sk::util::Object
      {
        public:
          Dispatcher();
          virtual ~Dispatcher();

          long long makeSequence();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          static Dispatcher& main();
          static void cleanup();
      
        private:
          Dispatcher(const Dispatcher& other);
          Dispatcher& operator = (const Dispatcher& other);

          long long _sequence;
          static sk::util::Holder<Dispatcher> _mainHolder;
          sk::rt::thread::Mutex _mutex;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_DISPATCHER_H_ */
