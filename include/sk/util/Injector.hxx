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
    template<typename F, typename T>
    class Injector 
      : public virtual sk::util::Mapper<F, T>
    {
      public:
        Injector(const sk::util::List<F>& list);
        ~Injector();
    
        const T inject(const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<F, T>& reducer) const;
        const T inject(const T& initial, const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<F, T>& reducer) const;
        T& inject(T& memo, const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<F, T>& reducer) const;

        inline const T inject(const T& initial, const sk::util::Reducer<F, T>& reducer) const;
        inline T& inject(T& memo, const sk::util::Reducer<F, T>& reducer) const;
    
      protected:
        // sk::util::Mapper implementation.
        T map(F& object) const;

      private:
        Injector(const Injector<F, T>& other);
        Injector<F, T>& operator = (const Injector<F, T>& other);

        const sk::util::List<F>& _list;
    };
  }
}

template<typename F, typename T>
inline const T
sk::util::Injector<F, T>::
inject(const T& initial, const sk::util::Reducer<T>& reducer)
{
  return inject(initial, *this, reducer)
}

template<typename F, typename T>
inline T&
sk::util::Injector<F, T>::
inject(T& memo, const sk::util::Reducer<T>& reducer)
{
  return inject(memo, *this, reducer);
}

#endif /* _SK_UTIL_INJECTOR_HXX_ */
