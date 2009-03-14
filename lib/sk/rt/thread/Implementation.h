/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_IMPLEMENTATION_H_
#define _SK_RT_THREAD_IMPLEMENTATION_H_

#include <sk/util/Object.h>
#include <sk/rt/thread/abstract/Implementation.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Implementation 
        : public virtual sk::util::Object
      {
        public:
          Implementation();
          virtual ~Implementation();

          static abstract::Implementation& instance();
          static void reset();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Implementation(const Implementation& other);
          Implementation& operator = (const Implementation& other);

          static abstract::Implementation* _implementation;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_IMPLEMENTATION_H_ */
