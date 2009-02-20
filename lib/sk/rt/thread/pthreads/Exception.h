/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_EXCEPTION_H_
#define _SK_RT_THREAD_PTHREADS_EXCEPTION_H_

#include <sk/util/SystemException.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Exception 
          : public sk::util::SystemException
        {
          public:
            Exception(const sk::util::String& function, int code);
            virtual ~Exception() throw();
        
            static bool raiseUnlessSuccess(const sk::util::String& name, int status, int other = 0);
            const sk::util::String getFunctionName() const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Exception(const Exception& other);
            Exception& operator = (const Exception& other);

            sk::util::String _function;
        };
      }
    }
  }
}

#define SK_PTHREAD_RAISE_UNLESS_SUCCESS(function, args) sk::rt::thread::pthreads::Exception::raiseUnlessSuccess(#function, function/**/args)
#define SK_PTHREAD_RAISE_UNLESS_SUCCESS_OR(other, function, args) sk::rt::thread::pthreads::Exception::raiseUnlessSuccess(#function, function/**/args, other)

#endif /* _SK_RT_THREAD_PTHREADS_EXCEPTION_H_ */
