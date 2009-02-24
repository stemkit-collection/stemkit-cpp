/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_INSPECTOR_H_
#define _SK_RT_THREAD_INSPECTOR_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/rt/thread/Generic.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Inspector 
        : public virtual sk::util::Object
      {
        public:
          Inspector(const thread::Generic& thread);
          virtual ~Inspector();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        private:
          Inspector(const Inspector& other);
          Inspector& operator = (const Inspector& other);

          const thread::Generic& _thread;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_INSPECTOR_H_ */
