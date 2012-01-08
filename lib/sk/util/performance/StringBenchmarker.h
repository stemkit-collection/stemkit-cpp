/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PERFORMANCE_STRINGBENCHMARKER_H_
#define _SK_UTIL_PERFORMANCE_STRINGBENCHMARKER_H_

#include <sk/util/Object.h>
#include <sk/rt/Benchmarker.h>

namespace sk {
  namespace util {
    namespace performance {
      class StringBenchmarker
        : public sk::rt::Benchmarker
      {
        public:
          StringBenchmarker();
          virtual ~StringBenchmarker();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          // sk::rt::Benchmarker re-implementation.
          void setUp();

        private:
          StringBenchmarker(const StringBenchmarker& other);
          StringBenchmarker& operator = (const StringBenchmarker& other);
      };
    }
  }
}

#endif /* _SK_UTIL_PERFORMANCE_STRINGBENCHMARKER_H_ */
