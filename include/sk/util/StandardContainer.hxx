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
        T& getMutable(const Selector<T>& selector) const;

        bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const;
        bool findMutable(sk::util::Holder<T>& holder, const Selector<T>& selector) const;

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
        T& getMutable(int index) const;

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
        
        void addFirst(const T& object);
        void addFirst(T& object);
        void addFirst(T* object);
        
        void addLast(const T& object);
        void addLast(T& object);
        void addLast(T* object);

        const T& getFirst() const;
        const T& getLast() const;
        T& getMutableFirst() const;
        T& getMutableLast() const;

        void removeFirst();
        void removeLast();
        T* cutoffFirst();
        T* cutoffLast();

        const sk::util::String join(const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper) const;
        const sk::util::String join(const sk::util::String& separator) const;
        const sk::util::String join() const;

        // sk::util::Object implementation.
        const sk::util::Class getClass() const;
        const String inspect() const;
        const String toString() const;

      protected:
        struct AssessingBinaryFunctor;

        static inline typename Policy::slot_storage_t makeStorage(const T& object);
        static inline typename Policy::slot_storage_t makeStorage(T& object);
        static inline typename Policy::slot_storage_t makeStorage(T* object);

        inline void add(typename Type::container_t::iterator position, typename Policy::slot_storage_t storage);
        inline typename Type::container_t::iterator remove(typename Type::container_t::iterator position);
        inline T* cutoff(typename Type::container_t::iterator position);
        inline T* release(typename Type::container_t::iterator position);
    
        typename Type::container_t _container;

      private:
        StandardContainer(const StandardContainer<T, Policy, Type>& other);
        StandardContainer<T, Policy, Type>& operator = (const StandardContainer<T, Policy, Type>& other);

        inline typename Type::container_t::iterator position(int index, int tailOffset);
        inline typename Type::container_t::const_iterator position(int index, int tailOffset) const;

        struct Cleaner;
        struct SelectingFunctor;
        struct ConstProcessingFunctor;
        struct ProcessingFunctor;
    };
  }
}

#endif /* _SK_UTIL_STANDARDCONTAINER_HXX_ */
