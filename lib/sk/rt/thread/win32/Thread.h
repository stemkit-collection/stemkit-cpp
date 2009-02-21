/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_WIN32_THREAD_H_
#define _SK_RT_THREAD_WIN32_THREAD_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace win32 {
        class Thread 
          : public virtual sk::util::Object
        {
          public:
            Thread();
            virtual ~Thread();
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Thread(const Thread& other);
            Thread& operator = (const Thread& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_WIN32_THREAD_H_ */
