/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_PROBE_
#define _SK_UTIL_TEST_PROBE_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    namespace test {
      class Probe
        : public virtual sk::util::Object 
      {
        public:
          Probe(const sk::util::String& name);
          virtual ~Probe();

          const sk::util::String getName() const;

          static void resetCounter();
          static int getCounter();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Probe(const Probe& other);
          Probe& operator = (const Probe& other);

          sk::util::String _name;
          static int _counter;
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_PROBE_ */
