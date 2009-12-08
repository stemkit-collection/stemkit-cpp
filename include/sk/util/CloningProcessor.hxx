/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_CLONINGPROCESSOR_HXX_
#define _SK_UTIL_CLONINGPROCESSOR_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    template<typename T>
    class CloningProcessor 
      : public virtual sk::util::Processor<T>
    {
      public:
        CloningProcessor(sk::util::Collection<T>& depot);
        ~CloningProcessor();
    
        void process(T& object) const;
    
      private:
        CloningProcessor<T>& operator = (const CloningProcessor<T>& other);

        sk::util::Collection<T>& _depot;
    };
  }
}

#endif /* _SK_UTIL_CLONINGPROCESSOR_HXX_ */
