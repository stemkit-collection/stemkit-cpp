/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ARRAYLIST_
#define _SK_UTIL_ARRAYLIST_

#include <sk/util/AbstractList.h>
#include <sk/util/Class.h>
#include <deque>

namespace sk {
  namespace util {
    template<class T>
    class ArrayList
      : public sk::util::AbstractList<T>
    {
      public:
        ArrayList();
        virtual ~ArrayList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::util::Collection<T> implementation.
        void clear();
        
      private:
        ArrayList(const ArrayList<T>& other);
        ArrayList<T>& operator = (const ArrayList<T>& other);

        typedef Slot<T>* item;
        typedef std::allocator<item> allocator;
        typedef std::deque<item, allocator> container;

        container _container;
    };
  }
}

template<class T>
sk::util::ArrayList<T>::
ArrayList()
{
}

template<class T>
sk::util::ArrayList<T>::
~ArrayList()
{
  (*this).clear();
}

template<class T>
const sk::util::Class
sk::util::ArrayList<T>::
getClass() const
{
  return sk::util::Class("sk::util::ArrayList");
}

template<class T>
void
sk::util::ArrayList<T>::
clear()
{
  _container.clear();
}

#endif /* _SK_UTIL_ARRAYLIST_ */
