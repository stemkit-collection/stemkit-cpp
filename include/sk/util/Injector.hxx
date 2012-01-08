/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_INJECTOR_HXX_
#define _SK_UTIL_INJECTOR_HXX_

#include <sk/util/List.h>
#include <sk/util/Reducer.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    template<typename F, typename T = F>
    class Injector
      : public virtual sk::util::Object
    {
      public:
        Injector(const sk::util::List<F>& list);
        ~Injector();

        const T inject(const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const;
        const T inject(const sk::util::Reducer<F, T>& reducer) const;
        const T inject(const T& initial, const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const;
        T& inject(T& memo, const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const;

        inline const T inject(const T& initial, const sk::util::Reducer<F, T>& reducer) const;
        inline T& inject(T& memo, const sk::util::Reducer<F, T>& reducer) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Injector(const Injector<F, T>& other);
        Injector<F, T>& operator = (const Injector<F, T>& other);

        struct Processor;
        const sk::util::List<F>& _list;
    };
  }
}

#endif /* _SK_UTIL_INJECTOR_HXX_ */
