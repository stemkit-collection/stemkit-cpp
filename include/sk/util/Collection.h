/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
#include <sk/util/Assessor.h>

namespace sk {
  namespace util {
    template<class T>
    class Collection
      : public virtual sk::util::Object 
    {
      public:
        /// Returns an immutalbe element for which the specified selector 
        /// assesses to true. Throws sk::util::NoSuchElementException if
        /// such an element is not present in this collection.
        virtual const T& get(const Selector<T>& selector) const = 0;
        
        /// Returns a mutalbe element for which the specified selector assesses 
        /// to true. Throws sk::util::NoSuchElementException if such an element 
        /// is not present in this collection. In case the found element is not
        /// mutalbe, exception sk::util::IllegalStateException is thrown.
        virtual T& getMutable(const Selector<T>& selector) = 0;

        //@{
        /// Finds an element for which the specified selector assesses to true
        /// and places it into the specified holder. Returns true if such an
        /// element was found, false otherwise. If a mmutable element holder
        /// is specified but the collection element is immutalbe, exception
        /// sk::util::IllegalStateException is thrown.
        virtual bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) const = 0;
        virtual bool find(sk::util::Holder<T>& holder, const Selector<T>& selector) = 0;
        //@}

        //@{
        /// Iterates over all the elements in this collection invoking the
        /// specified processor's method process() for each element. When a
        /// mutable element processor is specified, but an immutalbe element
        /// is encountered, exception sk::util::IllegalStateException is
        /// thrown. Iteration may be stopped by throwing sk::util::Break from
        /// the processor's method process().
        virtual void forEach(const Processor<const T>& processor) const = 0;
        virtual void forEach(const Processor<T>& processor) = 0;
        //@}

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

        /// Returns true if this collection contains all of the elements in
        /// the specified collection according to the specified assessor.
        virtual bool containsAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) const = 0;

        //@{
        /// Ensures that this collection contains the specified element.
        /// When added as a pointer, the pointer ownership is assumed.
        virtual bool add(const T& object) = 0;
        virtual bool add(T& object) = 0;
        virtual bool add(T* object) = 0;
        //@}

        /// Removes all of the elements from this collection.
        virtual void clear() = 0;

        /// Removes a single instance of the specified element from this
        /// collection, if any. Returns true if such an element was present,
        /// false otherwise.
        virtual bool remove(const T& object) = 0;

        /// Removes a single element from this collection for which the
        /// specified selector assesses to true. Returns true if such an 
        /// element was present, false otherwise.
        virtual bool remove(const Selector<T>& selector) = 0;

        /// Removes a single instance of the specified element from this
        /// collection, and returns the element as a pointer. The caller 
        /// is responsible for deleting the pointer. Throws exception
        /// sk::util::NoSuchElementException when the element was not 
        /// present in this collection. When the collection does not own
        /// the element exception sk::util::UnsupportedOperationException
        /// is thrown.
        virtual T* cutoff(const T& object) = 0;
        
        /// Removes a single element from this colleciton for which the
        /// specified selector assesses to true and returns the element 
        /// as a pointer. The caller is responsible for deleting the 
        /// pointer. Throws exception sk::util::NoSuchElementException 
        /// when the element was not present in this collection. When 
        /// the collection does not own the elemen, exception
        /// sk::util::NoSuchElementException is thrown.
        virtual T* cutoff(const Selector<T>& selector) = 0;

        //@{
        /// Same as for cutoff(), however the element is not removed from the
        /// collection, being replaced by a reference instead. It performs 
        /// just the ownership release. Again, the caller is responsible for 
        /// the actual poiner deletion.
        virtual T* release(const T& object) = 0;
        virtual T* release(const Selector<T>& selector) = 0;
        //@}

        /// Removes all of this collection's elements that are also contained in
        /// the specified collection. Returns true if the collection has been 
        /// modified, false otherwise.
        virtual bool removeAll(const Collection<T>& other) = 0;
        
        /// Removes all of this collection's elements that are also contained in
        /// the specified collection according to the specified assessor. 
        /// Returns true if the collection has been modified, false otherwise.
        virtual bool removeAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) = 0;

        /// Removes all of this collection's elements for which the specified
        /// selector assesses to true. Returns true if the collection has been 
        /// modified, false otherwise.
        virtual bool removeAll(const Selector<T>& selector) = 0;

        /// Retains only the elements in this collection that are contained in
        /// the specified collection. Returns true if the collection has been 
        /// modified, false otherwise.
        virtual bool retainAll(const Collection<T>& other) = 0;
        
        /// Retains only the elements in this collection that are contained in
        /// the specified collection according to the specified assessor. 
        /// Returns true if the collection has been modified, false otherwise.
        virtual bool retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) = 0;

        /// Retains only the elements in this collection for which the
        /// specified selector assesses to true. Returns true if the 
        /// collection has been modified, false otherwise.
        virtual bool retainAll(const Selector<T>& selector) = 0;
    };
  }
}

#endif /* _SK_UTIL_COLLECTION_ */
