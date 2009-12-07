/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SELECTINGPROCESSOR_HXX_
#define _SK_UTIL_SELECTINGPROCESSOR_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    template<typename T>
    class SelectingProcessor 
      : public virtual sk::util::Processor<T>
    {
      public:
        SelectingProcessor(const sk::util::Processor<T>& processor, const sk::util::Selector<T>& selector);
        SelectingProcessor(const SelectingProcessor<T>& other);
        ~SelectingProcessor();
    
        void process(T& object) const;
    
      private:
        SelectingProcessor<T>& operator = (const SelectingProcessor<T>& other);

        const sk::util::Processor<T>& _processor;
        const sk::util::Selector<T>& _selector;
    };
  }
}

#endif /* _SK_UTIL_SELECTINGPROCESSOR_HXX_ */
