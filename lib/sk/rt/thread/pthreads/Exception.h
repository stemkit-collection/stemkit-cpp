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

#include <sk/rt/SystemException.h>
#include <sk/util/Integers.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        class Exception 
          : public sk::rt::SystemException
        {
          public:
            Exception(const sk::util::String& function, int code);
            virtual ~Exception() throw();
        
            static bool raiseUnlessSuccess(const sk::util::String& statement, int status);
            static bool raiseUnlessSuccess(const sk::util::String& statement, int status, const sk::util::Integers& others);
            const sk::util::String getFunctionName() const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Exception& operator = (const Exception& other);

            sk::util::String _function;
        };
      }
    }
  }
}

#define SK_PTHREAD_RAISE_UNLESS_SUCCESS(statement) sk::rt::thread::pthreads::Exception::raiseUnlessSuccess(#statement, statement)
#define SK_PTHREAD_RAISE_UNLESS_SUCCESS_OR(other, statement) sk::rt::thread::pthreads::Exception::raiseUnlessSuccess(#statement, statement, other)

#endif /* _SK_RT_THREAD_PTHREADS_EXCEPTION_H_ */
