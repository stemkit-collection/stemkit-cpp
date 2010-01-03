/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PROCESSOR_SELECTING_HXX_
#define _SK_UTIL_PROCESSOR_SELECTING_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace processor {
      template<typename T>
      class Selecting : public virtual sk::util::Processor<T> {
        public:
          Selecting(const sk::util::Processor<T>& processor, const sk::util::Selector<T>& selector)
            : _processor(processor), _selector(selector) {}
      
          void process(T& object) const {
            if(_selector.assess(object) == true) {
              _processor.process(object);
            }
          }
      
        private:
          // Selecting(const Selecting<T>& other);
          Selecting<T>& operator = (const Selecting<T>& other);

          const sk::util::Processor<T>& _processor;
          const sk::util::Selector<T>& _selector;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_SELECTING_HXX_ */
