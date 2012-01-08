/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PROCESSOR_MAPPING_HXX_
#define _SK_UTIL_PROCESSOR_MAPPING_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    namespace processor {
      template<typename F, typename T = F>
      class Mapping : public virtual sk::util::Processor<F> {
        public:
          Mapping(const sk::util::Processor<T>& processor, const sk::util::Mapper<F, T>& mapper)
            : _processor(processor), _mapper(mapper) {}

          void process(F& object) const {
            _processor.process(_mapper.map(object));
          }

        private:
          // Mapping(const Mapping<F, T>& other);
          Mapping<F, T>& operator = (const Mapping<F, T>& other);

          const sk::util::Processor<T>& _processor;
          const sk::util::Mapper<F, T>& _mapper;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_MAPPING_HXX_ */
