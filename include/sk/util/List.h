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
        /// Inserts the specified element at the specified position in this 
        /// list. When added as a pointer, the pointer ownership is assumed.
        virtual void add(int index, const T& object) = 0;
        virtual void add(int index, T& object) = 0;
        virtual void add(int index, T* object) = 0;
        using Collection<T>::add;
        //@}
        
        //@{
        /// Returns the immutable element at the specified position in this 
        /// list. Throws sk::util::IndexOutOfBoundsException when a negative
        /// index or the one beyond the last element is specified.
        virtual const T& get(int index) const = 0;
        using Collection<T>::get;
        //@}

        //@{
        /// Returns the mutable element at the specified position in this 
        /// list. Throws sk::util::IndexOutOfBoundsException when a negative
        /// index or the one beyond the last element is specified.
        virtual T& getMutable(int index) = 0;
        using Collection<T>::getMutable;
        //@}

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

        //@{
        /// Removes the element at the specified position in this list.
        /// Shifts any subsequent elements to the left (subtracts one 
        /// from their indices). The element is actually destroyed when
        /// added to this list as a pointer.
        virtual void remove(int index) = 0;
        using Collection<T>::remove;
        //@}

        //@{
        /// Removes the element at the specified position in this list.
        /// Shifts any subsequent elements to the left (subtracts one 
        /// from their indices). Throws an exception when the element 
        /// was not added as a pointer. Otherwise returns a pointer to
        /// the element without destroying the latter.
        virtual T* cutoff(int index) = 0;
        using Collection<T>::cutoff;
        //@}

        //@{
        /// Same as for cutoff(), however the element is not removed from the
        /// collection, being replaced by a reference instead. It performs 
        /// just the ownership release. Again, the caller is responsible for 
        /// the actual poiner deletion.
        virtual T* release(int index) = 0;
        using Collection<T>::release;
        //@}

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
