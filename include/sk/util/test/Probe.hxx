/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_PROBE_HXX_
#define _SK_UTIL_TEST_PROBE_HXX_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace test {
      template<typename T>
      class Probe
        : public T
      {
        public:
          Probe(const T& object);
          Probe(const Probe<T>& other);
          ~Probe();

          static void resetCounter();
          static int getCounter();

        private:
          Probe<T>& operator = (const Probe<T>& other);

          static int _counter;
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_PROBE_HXX_ */
