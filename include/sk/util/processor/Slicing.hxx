/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PROCESSOR_SLICING_HXX_
#define _SK_UTIL_PROCESSOR_SLICING_HXX_

#include <sk/util/Processor.h>
#include <sk/util/Break.h>

namespace sk {
  namespace util {
    namespace processor {
      template<typename T>
      class Slicing : public virtual sk::util::Processor<T> {
        public:
          Slicing(int start, int end, const sk::util::Processor<T>& processor)
            : _processor(processor), _start(start), _end(end), _index(0) {}

          void process(T& object) const {
            if(_end >=0 && _index >= _end) {
              throw sk::util::Break();
            }
            if(_index++ >= _start) {
              _processor.process(object);
            }
          }

        private:
          // Slicing(const Slicing<T>& other);
          Slicing<T>& operator = (const Slicing<T>& other);

          const sk::util::Processor<T>& _processor;
          const int _start;
          const int _end;
          mutable int _index;
      };
    }
  }
}

#endif /* _SK_UTIL_PROCESSOR_SLICING_HXX_ */
