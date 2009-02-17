/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_UNCAUGHTEXCEPTIONHANDLER_H_
#define _SK_RT_THREAD_UNCAUGHTEXCEPTIONHANDLER_H_

#include <sk/util/Object.h>
#include <exception>

namespace sk {
  namespace rt {
    namespace thread {
      class Generic;

      class UncaughtExceptionHandler 
        : public virtual sk::util::Object
      {
        public:
          virtual void uncaughtException(sk::rt::thread::Generic& thread, const std::exception& exception) = 0;
          virtual void uncaughtException(sk::rt::thread::Generic& thread) = 0;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_UNCAUGHTEXCEPTIONHANDLER_H_ */
