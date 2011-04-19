/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ITEMS_HXX_
#define _SK_UTIL_ITEMS_HXX_

#include <sk/util/ArrayList.hxx>
#include <sk/util/String.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    template<typename T>
    class Items 
      : public sk::util::ArrayList<T>::Copying
    {
      public:
        Items();
        Items(const sk::util::Items<T>& other);
        explicit Items(const T& item);
        virtual ~Items();

        const T& first() const;
        const T& last() const;
        const T pop();
        const T shift();

        const sk::util::Items<T> slice(int start, int end) const;
        const sk::util::Items<T> slice(int end) const;
        const sk::util::Items<T> map(const sk::util::Mapper<const T>& mapper) const;

        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue, const sk::util::Mapper<const T, const sk::util::String>& mapper) const;
        using sk::util::ArrayList<T>::Copying::join;

        sk::util::Items<T> operator + (const T& item) const;
        sk::util::Items<T> operator + (const sk::util::Items<T>& other) const;
        sk::util::Items<T>& operator = (const sk::util::Items<T>& other);
        sk::util::Items<T>& operator << (const T& item);
        sk::util::Items<T>& operator << (const sk::util::Items<T>& other);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
        const sk::util::String inspect() const;

      private:
        typedef typename sk::util::ArrayList<T>::Copying super_t;
        struct Propagator;
    };
  }
}

#endif /* _SK_UTIL_ITEMS_HXX_ */
