/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_RANDOMACCESSCONTAINER_HXX_
#define _SK_UTIL_RANDOMACCESSCONTAINER_HXX_

#include <sk/util/StandardContainer.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy, typename Type>
    class RandomAccessContainer 
      : public sk::util::StandardContainer<T, Policy, Type>
    {
      typedef sk::util::StandardContainer<T, Policy, Type> super_t;

      public:
        RandomAccessContainer();
        ~RandomAccessContainer();

        // sk::util::StandardContainer re-implementation.
        void add(int index, const T& object);
        void add(int index, T& object);
        void add(int index, T* object);
        using super_t::add;

        const T& get(int index) const;
        using super_t::get;

        T& getMutable(int index) const;
        using super_t::getMutable;

        void remove(int index);
        using super_t::remove;

        T* cutoff(int index);
        using super_t::cutoff;

        T* release(int index);
        using super_t::release;

        void set(int index, const T& object);
        void set(int index, T& object);
        void set(int index, T* object);
        using super_t::set;

        void sort(const sk::util::BinaryAssessor<T>& assessor);
        using super_t::sort;

        void shuffle();
        
        // sk::util::Object implementation.
        const sk::util::Class getClass() const;
    
      private:
        RandomAccessContainer(const RandomAccessContainer<T, Policy, Type>& other);
        RandomAccessContainer<T, Policy, Type>& operator = (const RandomAccessContainer<T, Policy, Type>& other);

        inline typename Type::container_t::iterator position(int index, int size);
        inline typename Type::container_t::const_iterator position(int index, int size) const;
    };
  }
}

#endif /* _SK_UTIL_RANDOMACCESSCONTAINER_HXX_ */
