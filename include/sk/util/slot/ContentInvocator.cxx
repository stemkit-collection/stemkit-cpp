/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SLOTCONTENTINVOCATOR_CXX_
#define _SK_UTIL_SLOTCONTENTINVOCATOR_CXX_

#include <sk/util/slot/Processor.h>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T>
      class ContentInvocator 
        : public virtual sk::util::slot::Processor<T> 
      {
        public:
          ContentInvocator(const sk::util::Processor<T>& processor)
            : _processor(processor) {}
      
          bool process(const sk::util::Slot<T>& slot) const {
            _processor.process(slot.get());
            return false;
          }
      
        private:
          const sk::util::Processor<T>& _processor;
      };
    }
  }
}

#endif /* _SK_UTIL_SLOTCONTENTINVOCATOR_CXX_ */
