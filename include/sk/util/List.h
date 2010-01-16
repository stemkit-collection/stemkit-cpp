/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_LIST_
#define _SK_UTIL_LIST_

#include <sk/util/Collection.h>
#include <sk/util/Assessor.h>

namespace sk {
  namespace util {
    template<class T>
    class List
      : public virtual sk::util::Collection<T>
    {
      public:
        //@{
        /// Appends the specified element to the end of this list. When added 
        /// as a pointer, the pointer ownership is assumed.
        virtual bool add(const T& object) = 0;
        virtual bool add(T& object) = 0;
        virtual bool add(T* object) = 0;
        //@}
        
        //@{
        /// Inserts the specified element at the specified position in this 
        /// list. When added as a pointer, the pointer ownership is assumed.
        virtual void add(int index, const T& object) = 0;
        virtual void add(int index, T& object) = 0;
        virtual void add(int index, T* object) = 0;
        //@}

        using Collection<T>::add;
        
        //@{
        /// Inserts the given element at the beginning of this list. When 
        /// added as a pointer, the pointer ownership is assumed.
        virtual void addFirst(const T& object) = 0;
        virtual void addFirst(T& object) = 0;
        virtual void addFirst(T* object) = 0;
        //@}

        //@{
        /// Appends the given element to the end of this list. When added as 
        /// a pointer, the pointer ownership is assumed.
        // TODO: virtual void addLast(const T& object) = 0;
        // TODO: virtual void addLast(T& object) = 0;
        // TODO: virtual void addLast(T* object) = 0;
        //@}

        /// Returns the immutable element at the specified position in this 
        /// list. Throws sk::util::IndexOutOfBoundsException when a negative
        /// index or the one beyond the last element is specified.
        virtual const T& get(int index) const = 0;

        using Collection<T>::get;

        /// Returns the first element in this list as immutable. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual const T& getFirst() const = 0;

        /// Returns the last element in this list as immutable. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual const T& getLast() const = 0;

        /// Returns the mutable element at the specified position in this 
        /// list. Throws sk::util::IndexOutOfBoundsException when a negative
        /// index or the one beyond the last element is specified.
        virtual T& getMutable(int index) const = 0;

        using Collection<T>::getMutable;

        /// Returns the first element in this list as mutable. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual T& getMutableFirst() const = 0;

        /// Returns the last element in this list as mutable. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual T& getMutableLast() const = 0;

        /// Returns the index in this list of the first occurrence of the
        /// specified element, or -1 if this list does not contain this 
        /// element.
        virtual int indexOf(const T& object) const = 0;
        
        /// Returns the index in this list of the first occurrence of the
        /// element for which the specified selector assesses to true, or 
        /// 1 if this list does not contain such an element.
        virtual int indexOf(const Selector<T>& selector) const = 0;

        /// Returns the index in this list of the last occurrence of the
        /// specified element, or -1 if this list does not contain this 
        /// element.
        virtual int lastIndexOf(const T& object) const = 0;

        /// Returns the index in this list of the last occurrence of the
        /// element for which the specified selector assesses to true, or 
        /// 1 if this list does not contain such an element.
        virtual int lastIndexOf(const Selector<T>& selector) const = 0;

        /// Removes the element at the specified position in this list.
        /// Shifts any subsequent elements to the left (subtracts one 
        /// from their indices). The element is actually destroyed when
        /// added to this list as a pointer.
        virtual void remove(int index) = 0;

        using Collection<T>::remove;

        /// Removes the first element from this list. The element is 
        /// actually destroyed when added to this list as a pointer. 
        /// Throws sk::util::NoSuchElementException when the list is 
        /// empty.
        // TODO: virtual void removeFirst() = 0;

        /// Removes the last element from this list. The element is 
        /// actually destroyed when added to this list as a pointer. 
        /// Throws sk::util::NoSuchElementException when the list is
        /// empty.
        // TODO: virtual void removeLast() = 0;

        /// Removes the element at the specified position in this list.
        /// Shifts any subsequent elements to the left (subtracts one 
        /// from their indices). Throws an exception when the element 
        /// was not added as a pointer. Otherwise returns a pointer to
        /// the element without destroying it.
        virtual T* cutoff(int index) = 0;

        using Collection<T>::cutoff;

        /// Removes the first element from this list. Throws an exception 
        /// when the element was not added as a pointer. Otherwise returns 
        /// a pointer to the element without destroying it. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual T* cutoffFirst() = 0;

        /// Removes the last element from this list. Throws an exception 
        /// when the element was not added as a pointer. Otherwise returns 
        /// a pointer to the element without destroying it. Throws 
        /// sk::util::NoSuchElementException when the list is empty.
        // TODO: virtual T* cutoffLast() = 0;

        /// Same as for cutoff(), however the element is not removed from the
        /// collection, being replaced by a reference instead. It performs 
        /// just the ownership release. The caller is responsible for the 
        /// actual pointer deletion.
        virtual T* release(int index) = 0;

        using Collection<T>::release;

        //@{
        /// Replaces the element at the specified position in this list with
        /// the specified element. When a pointer is specified, the pointer 
        /// ownership is assumed.
        virtual void set(int index, const T& object) = 0;
        virtual void set(int index, T& object) = 0;
        virtual void set(int index, T* object) = 0;
        //@}

        /// Sorts the specified list into ascending order, according to the
        /// natural ordering of its elements.
        virtual void sort() = 0;

        /// Sorts the specified list according to the order induced by the
        /// specified assessor.
        virtual void sort(const sk::util::BinaryAssessor<T>& assessor) = 0;
        
        /// Randomly permutes the list using a default source of randomness.
        virtual void shuffle() = 0;

        /// Reverses the order of the elements in this list.
        virtual void reverse() = 0;
    };
  }
}

#endif /* _SK_UTIL_LIST_ */
