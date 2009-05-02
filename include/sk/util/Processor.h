/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_PROCESSOR_
#define _SK_UTIL_PROCESSOR_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    template<class T>
    class UnaryProcessor
      : public virtual sk::util::Object 
    {
      public:
        virtual void process(T& o) const = 0;
    };

    template<class T1, class T2>
    class BinaryProcessor
      : public virtual sk::util::Object 
    {
      public:
        virtual void process(T1& o1, T2& o2) const = 0;
    };

    template<class T>
    class Processor
      : public virtual sk::util::UnaryProcessor<T>
    {
    };
  }
}

#endif /* _SK_UTIL_PROCESSOR_ */
