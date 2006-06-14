/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_
#define _SK_UTIL_ABSTRACTCOLLECTION_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class AbstractCollection
      : public virtual sk::util::Object 
    {
      public:
        AbstractCollection();
        virtual ~AbstractCollection();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        AbstractCollection(const AbstractCollection& other);
        AbstractCollection& operator = (const AbstractCollection& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_ */
