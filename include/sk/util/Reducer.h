/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_REDUCER_H_
#define _SK_UTIL_REDUCER_H_

#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    template<typename F, typename T = F>
    class Reducer 
    {
      public:
        virtual T reduce(T memo, const F& object, const sk::util::Mapper<F, T>& mapper) const = 0;

      private:
        struct Processor;
    };
  }
}

#endif /* _SK_UTIL_REDUCER_H_ */
