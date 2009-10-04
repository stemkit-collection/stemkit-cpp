/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_COLLECTION_
#define _SK_UTIL_COLLECTION_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/util/Selector.h>
#include <sk/util/Processor.h>

namespace sk {
  namespace util {
    template<class T>
    class Collection
      : public virtual sk::util::Object 
    {
      public:
        virtual T& get(const Selector<T>& selector) const = 0;
        virtual void forEach(const Processor<T>& processor) const = 0;
        virtual bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const = 0;

        /// Returns true if this collection contains no elements.
        virtual bool isEmpty() const = 0;

        /// Returns the number of elements in this collection.
        virtual int size() const = 0;

        /// Returns true if this collection contains the specified element.
        virtual bool contains(const T& object) const = 0;

        /// Returns true if the specified selector assesses to true for any
        /// element of this collection.
        virtual bool contains(const Selector<T>& selector) const = 0;

        /// Returns true if this collection contains all of the elements in
        /// the specified collection.
        virtual bool containsAll(const Collection<T>& other) const = 0;

        /// Ensures that this collection contains the specified element. A
        /// reference is added as needed.
        virtual bool add(T& object) = 0;

        /// Ensures that this collection contains the specified element. A
        /// pointer ownership will be assumed.
        virtual bool add(T* object) = 0;

        /// Adds all of the elements in the specified collection to this
        /// collection.
        virtual bool addAll(const Collection<T>& other) = 0;
        
        /// Moves all of the elements from the specified collection to this
        /// collection.
        virtual bool moveAll(Collection<T>& other) = 0;

        /// Removes all of the elements from this collection.
        virtual void clear() = 0;

        /// Removes a single instance of the specified element from this
        /// collection, if it is present.
        virtual bool remove(const T& object) = 0;

        /// Removes a single element from this collection for which the
        /// specified selector assesses to true.
        virtual bool remove(const Selector<T>& selector) = 0;

        virtual T* cutoff(const T& object) = 0;
        virtual T* cutoff(const Selector<T>& selector) = 0;
        virtual T* release(const T& object) = 0;
        virtual T* release(const Selector<T>& selector) = 0;

        /// Removes all of this collection's elements that are also contained in
        /// the specified collection.
        virtual bool removeAll(const Collection<T>& other) = 0;

        /// Removes all of this collection's elements for which the specified
        /// selector assesses to true.
        virtual bool removeAll(const Selector<T>& selector) = 0;

        /// Retains only the elements in this collection that are contained in
        /// the specified collection.
        virtual bool retainAll(const Collection<T>& other) = 0;

        /// Retains only the elements in this collection for whitch the
        /// specified selector assesses to true.
        virtual bool retainAll(const Selector<T>& selector) = 0;
    };
  }
}

#endif /* _SK_UTIL_COLLECTION_ */
