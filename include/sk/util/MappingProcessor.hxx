/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_MAPPINGPROCESSOR_HXX_
#define _SK_UTIL_MAPPINGPROCESSOR_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    template<typename F, typename T>
    class MappingProcessor 
      : public virtual sk::util::Processor<F>
    {
      public:
        MappingProcessor(const sk::util::Processor<T>& processor, const sk::util::Mapper<F, T>& mapper);
        MappingProcessor(const MappingProcessor<F, T>& other);
        ~MappingProcessor();
    
        void process(F& object) const;
    
      private:
        MappingProcessor<F, T>& operator = (const MappingProcessor<F, T>& other);

        const sk::util::Processor<T>& _processor;
        const sk::util::Mapper<F, T>& _mapper;
    };
  }
}

#endif /* _SK_UTIL_MAPPINGPROCESSOR_HXX_ */
