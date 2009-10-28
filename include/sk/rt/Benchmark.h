/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_BENCHMARK_H_
#define _SK_RT_BENCHMARK_H_

#include <sk/util/Object.h>
#include <sk/rt/Benchmarkable.h>

namespace sk {
  namespace rt {
    class Benchmark 
      : public virtual sk::rt::Benchmarkable
    {
      public:
        // sk::rt::Benchmarkable implementation
        void setup();
        void reset();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_RT_BENCHMARK_H_ */
