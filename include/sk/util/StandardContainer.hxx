/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STANDARDCONTAINER_HXX_
#define _SK_UTIL_STANDARDCONTAINER_HXX_

#include <sk/util/Collection.h>
#include <sk/util/List.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    template<typename T, typename Policy, typename Type>
    class StandardContainer 
      : public virtual sk::util::Collection<T>,
        public virtual sk::util::List<T>
    {
      public:
        StandardContainer();
        ~StandardContainer();

        // sk::util::Collection implementation.
        const T& get(const Selector<T>& selector) const;
        T& getMutable(const Selector<T>& selector);

        bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const;
        bool findMutable(sk::util::Holder<T>& holder, const Selector<T>& selector);

        void forEach(const Processor<const T>& processor) const;
        void forEach(const Processor<T>& processor);

        bool isEmpty() const;
        int size() const;

        bool contains(const T& object) const;
        bool contains(const Selector<T>& selector) const;
        bool containsAll(const Collection<T>& other) const;
        bool containsAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) const;

        bool add(const T& object);
        bool add(T& object);
        bool add(T* object);

        void clear();
        bool remove(const T& object);
        bool remove(const Selector<T>& selector);

        T* cutoff(const T& object);
        T* cutoff(const Selector<T>& selector);
        T* release(const T& object);
        T* release(const Selector<T>& selector);

        bool removeAll(const Collection<T>& other);
        bool removeAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor);
        bool removeAll(const Selector<T>& selector);

        bool retainAll(const Collection<T>& other);
        bool retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor);
        bool retainAll(const Selector<T>& selector);
        
        // sk::util::List implementation.
        void add(int index, const T& object);
        void add(int index, T& object);
        void add(int index, T* object);

        const T& get(int index) const;
        T& getMutable(int index);

        int indexOf(const T& object) const;
        int indexOf(const Selector<T>& selector) const;
        int lastIndexOf(const T& object) const;
        int lastIndexOf(const Selector<T>& selector) const;

        void remove(int index);
        T* cutoff(int index);
        T* release(int index);

        void set(int index, const T& object);
        void set(int index, T& object);
        void set(int index, T* object);

        void sort();
        void sort(const sk::util::BinaryAssessor<T>& assessor);
        void shuffle();
        void reverse();
        
        // sk::util::Object implementation.
        const sk::util::Class getClass() const;
        const String inspect() const;
        const String toString() const;
    
      private:
        StandardContainer(const StandardContainer<T, Policy, Type>& other);
        StandardContainer<T, Policy, Type>& operator = (const StandardContainer<T, Policy, Type>& other);

        typedef typename Type::item_t item_t;
        typedef typename Type::container_t container_t;

        struct Cleaner;
        struct SelectingFunctor;
        struct ConstProcessingFunctor;
        struct ProcessingFunctor;

        container_t _container;
    };
  }
}

#endif /* _SK_UTIL_STANDARDCONTAINER_HXX_ */
