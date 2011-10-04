/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_TEST_PROBE_H_
#define _SK_C_TEST_PROBE_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>

#include <sk/C/handle_provider.hxx>
#include <sk/C/test/c_probe.h>

namespace sk {
  namespace C {
    namespace test {
      class Probe 
        : public sk::C::handle_provider<Probe, sk_c_test_ProbeHandle>,
          public virtual sk::util::Object
      {
        public:
          Probe(const sk::util::String& name);
          virtual ~Probe();

          void raiseException(const sk::util::String& message) const;

          static void resetInstanceCouner();
          static int getInstanceCouner();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        private:
          Probe(const Probe& other);
          Probe& operator = (const Probe& other);

          sk::util::String _name;
          static int __instanceCounter;
      };
    }
  }
}

#endif /* _SK_C_TEST_PROBE_H_ */
