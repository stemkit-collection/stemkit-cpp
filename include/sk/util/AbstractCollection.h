/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_
#define _SK_UTIL_ABSTRACTCOLLECTION_

#include <sk/util/Collection.h>

namespace sk {
  namespace util {
    template<class T>
    class AbstractCollection
      : public virtual sk::util::Collection<T>
    {
      public:
        virtual ~AbstractCollection();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        AbstractCollection();
        AbstractCollection(const AbstractCollection<T>& other);
        AbstractCollection<T>& operator = (const AbstractCollection<T>& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_ */
