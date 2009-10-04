/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SLOTCONTENTINVOCATOR_HXX_
#define _SK_UTIL_SLOTCONTENTINVOCATOR_HXX_

#include <sk/util/SlotProcessor.hxx>

namespace sk {
  namespace util {
    template<typename T>
    class SlotContentInvocator 
      : public virtual sk::util::SlotProcessor<T> 
    {
      public:
        SlotContentInvocator(const sk::util::Processor<T>& processor)
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

#endif /* _SK_UTIL_SLOTCONTENTINVOCATOR_HXX_ */
