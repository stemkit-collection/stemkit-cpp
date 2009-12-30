/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PROCESSOR_REJECTING_HXX_
#define _SK_UTIL_PROCESSOR_REJECTING_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    namespace processor {
      template<typename T>
      class RejectingProcessor : public virtual sk::util::Processor<T> {
        public:
          RejectingProcessor(const sk::util::Processor<T>& processor, const sk::util::Selector<T>& selector)
            : _processor(processor), _selector(selector) {}
      
          void process(T& object) const {
            if(_selector.assess(object) == false) {
              _processor.process(object);
            }
          }
      
        private:
          // RejectingProcessor(const RejectingProcessor<T>& other);
          RejectingProcessor<T>& operator = (const RejectingProcessor<T>& other);

          const sk::util::Processor<T>& _processor;
          const sk::util::Selector<T>& _selector;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_REJECTING_HXX_ */
