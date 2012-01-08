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
#include <sk/rt/Mutex.h>

#include "Main.h"
#include <sk/rt/thread/UncaughtExceptionHandler.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Dispatcher
        : public virtual sk::util::Object
      {
        public:
          Dispatcher();
          virtual ~Dispatcher();

          uint64_t makeSequence();
          sk::rt::thread::Generic& currentThread();

          void setUncaughtExceptionHandler(thread::UncaughtExceptionHandler& handler);
          void setUncaughtExceptionHandler(thread::UncaughtExceptionHandler* handler);
          thread::UncaughtExceptionHandler& getUncaughtExceptionHandler() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          static Dispatcher& main();
          static void reset();
          static bool isMainAvailable();

        private:
          Dispatcher(const Dispatcher& other);
          Dispatcher& operator = (const Dispatcher& other);

          uint64_t _sequence;
          static sk::util::Holder<Dispatcher> _mainHolder;
          static bool _mainAvailable;
          sk::rt::thread::Main _mainThread;
          sk::rt::Mutex _mutex;
          sk::util::Holder<sk::rt::thread::UncaughtExceptionHandler> _uncaughtExceptionHandlerHolder;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_DISPATCHER_H_ */
