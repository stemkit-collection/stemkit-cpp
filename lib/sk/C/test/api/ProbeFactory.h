/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_PROBEFACTORY_H_
#define _SK_UTIL_TEST_PROBEFACTORY_H_

#include <sk/util/Object.h>
#include <sk/util/ArrayList.hxx>

namespace sk {
  namespace util {
    namespace test {
      class Probe;

      class ProbeFactory 
        : public virtual sk::util::Object
      {
        public:
          ProbeFactory();
          virtual ~ProbeFactory();

          int getSize() const;
          sk::util::test::Probe& makeProbe(const sk::util::String& name);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          ProbeFactory(const ProbeFactory& other);
          ProbeFactory& operator = (const ProbeFactory& other);

          sk::util::ArrayList<sk::util::test::Probe> _probes;
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_PROBEFACTORY_H_ */
