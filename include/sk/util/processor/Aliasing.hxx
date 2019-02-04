/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PROCESSOR_ALIASING_HXX_
#define _SK_UTIL_PROCESSOR_ALIASING_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    namespace processor {
      template<typename F, typename T = F>
      class Aliasing : public virtual sk::util::Processor<F> {
        public:
          Aliasing(sk::util::Collection<T>& depot)
            : _depot(depot) {}
      
          void process(F& object) const {
            _depot.add(object);
          }
      
        private:
          // Aliasing(const Aliasing<F, T>& other);
          Aliasing<F, T>& operator = (const Aliasing<F, T>& other);

          sk::util::Collection<T>& _depot;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_ALIASING_HXX_ */
