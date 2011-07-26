/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PERFORMANCE_LINKEDLISTBENCHMARKER_H_
#define _SK_UTIL_PERFORMANCE_LINKEDLISTBENCHMARKER_H_

#include <sk/util/Object.h>
#include <sk/rt/Benchmarker.h>

namespace sk {
  namespace util {
    namespace performance {
      class LinkedListBenchmarker 
        : public sk::rt::Benchmarker
      {
        public:
          LinkedListBenchmarker();
          virtual ~LinkedListBenchmarker();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          // sk::rt::Benchmarker re-implementation.
          void setUp();

        private:
          LinkedListBenchmarker(const LinkedListBenchmarker& other);
          LinkedListBenchmarker& operator = (const LinkedListBenchmarker& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PERFORMANCE_LINKEDLISTBENCHMARKER_H_ */
