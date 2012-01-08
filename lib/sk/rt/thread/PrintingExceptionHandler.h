/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PRINTINGEXCEPTIONHANDLER_H_
#define _SK_RT_THREAD_PRINTINGEXCEPTIONHANDLER_H_

#include <sk/rt/thread/UncaughtExceptionHandler.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    namespace thread {
      class PrintingExceptionHandler
        : public virtual sk::rt::thread::UncaughtExceptionHandler
      {
        public:
          PrintingExceptionHandler(const sk::util::String& name);
          virtual ~PrintingExceptionHandler();

          // sk::util::thread::UncaughtExceptionHandler implementation.
          void uncaughtException(sk::rt::thread::Generic& thread, const std::exception& exception);
          void uncaughtException(sk::rt::thread::Generic& thread);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          PrintingExceptionHandler(const PrintingExceptionHandler& other);
          PrintingExceptionHandler& operator = (const PrintingExceptionHandler& other);

          void finalize();

          sk::rt::Scope _scope;
          bool _abortOnException;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_PRINTINGEXCEPTIONHANDLER_H_ */
