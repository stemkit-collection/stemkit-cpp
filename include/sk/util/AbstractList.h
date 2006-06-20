/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_
#define _SK_UTIL_ABSTRACTLIST_

#include <sk/util/AbstractCollection.h>
#include <sk/util/List.h>

namespace sk {
  namespace util {
    template<class T>
    class AbstractList
      : public sk::util::AbstractCollection<T>,
        public virtual sk::util::List<T> 
    {
      public:
        virtual ~AbstractList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        AbstractList();
        AbstractList(const AbstractList<T>& other);
        AbstractList<T>& operator = (const AbstractList<T>& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTLIST_ */
