/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_LIST_
#define _SK_UTIL_LIST_

#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    template<class T>
    class List
      : public virtual sk::util::Collection<T>
    {
      public:
        virtual void add(int index, T& object) = 0;
        virtual void add(int index, T* object) = 0;
        using Collection<T>::add;
        
        virtual bool addAll(int index, const Collection<T>& other) = 0;
        using Collection<T>::addAll;

        virtual bool moveAll(int index, const Collection<T>& other) = 0;
        using Collection<T>::moveAll;

        virtual T& get(int index) const = 0;
        using Collection<T>::get;

        virtual int indexOf(const T& object) const = 0;
        virtual int indexOf(const Selector<T>& selector) const = 0;

        virtual int lastIndexOf(const T& object) const = 0;
        virtual int lastIndexOf(const Selector<T>& selector) const = 0;

        virtual T& remove(int index) = 0;
        using Collection<T>::remove;

        virtual T* cutoff(int index) = 0;
        using Collection<T>::cutoff;

        virtual T* release(int index) = 0;
        using Collection<T>::release;

        virtual void set(int index, T& object) = 0;
        virtual void set(int index, T* object) = 0;
    };
  }
}

#endif /* _SK_UTIL_LIST_ */
