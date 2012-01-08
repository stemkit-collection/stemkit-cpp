/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PROCESSOR_COPYING_HXX_
#define _SK_UTIL_PROCESSOR_COPYING_HXX_

#include <sk/util/Processor.h>

namespace sk {
  namespace util {
    template<typename T> class Collection;

    namespace processor {
      template<typename F, typename T = F>
      class Copying : public virtual sk::util::Processor<const F> {
        public:
          Copying(sk::util::Collection<T>& depot)
            : _depot(depot) {}

          void process(const F& object) const {
            _depot.add(new T(object));
          }

        private:
          // Copying(const Copying<F, T>& other);
          Copying<F, T>& operator = (const Copying<F, T>& other);

          sk::util::Collection<T>& _depot;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_COPYING_HXX_ */
