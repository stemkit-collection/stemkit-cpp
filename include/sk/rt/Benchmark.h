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
#include <sk/util/String.h>
#include <sk/util/ArrayList.hxx>
#include <sk/rt/Runnable.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    class Benchmark 
      : public virtual sk::rt::Runnable
    {
      public:
        Benchmark(const sk::util::String& title);
        virtual ~Benchmark();

        void add(const sk::util::String& name, sk::rt::Runnable* code);
        void start();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Benchmark(const Benchmark& other);
        Benchmark& operator = (const Benchmark& other);

        // sk::rt::Runnable implementation.
        void run();
    
        sk::rt::Scope _scope;
        const sk::util::String _title;

        class Item;
        sk::util::ArrayList<Item> _items;
    };
  }
}

#endif /* _SK_RT_BENCHMARK_H_ */