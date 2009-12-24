/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_HXX_
#define _SK_UTIL_ABSTRACTCOLLECTION_HXX_

#include <sk/util/Collection.h>
#include <sk/util/Class.h>

#include <sk/util/slot/policy/Storing.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy = slot::policy::Storing<T> >
    class AbstractCollection
      : public virtual sk::util::Collection<T>
    {
      public:
        AbstractCollection();
        virtual ~AbstractCollection();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        // sk::util::Collection<T> implementation.
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

      protected:
        virtual void forEachSlot(const sk::util::Processor<const typename Policy::slot_t>& processor) const = 0;
        virtual void forEachSlot(const sk::util::Processor<typename Policy::slot_t>& processor) = 0;

      private:
        AbstractCollection(const AbstractCollection<T, Policy>& other);
        AbstractCollection<T, Policy>& operator = (const AbstractCollection<T, Policy>& other);

        struct Checker;
        struct Finder;
        struct MutableFinder;
        struct Invocator;
        struct MutableInvocator;
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_HXX_ */
