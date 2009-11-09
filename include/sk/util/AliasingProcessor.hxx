/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_ALIASINGPROCESSOR_HXX_
#define _SK_UTIL_ALIASINGPROCESSOR_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    template<typename T>
    class AliasingProcessor 
      : public virtual sk::util::Processor<T>
    {
      public:
        AliasingProcessor(sk::util::Collection<T>& depot);
        ~AliasingProcessor();
    
        void process(T& object) const;
    
      private:
        AliasingProcessor<T>& operator = (const AliasingProcessor<T>& other);

        sk::util::Collection<T>& _depot;
    };
  }
}

#endif /* _SK_UTIL_ALIASINGPROCESSOR_HXX_ */
