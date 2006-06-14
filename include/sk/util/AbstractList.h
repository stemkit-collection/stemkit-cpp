/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_
#define _SK_UTIL_ABSTRACTLIST_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class AbstractList
      : public virtual sk::util::Object 
    {
      public:
        AbstractList();
        virtual ~AbstractList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        AbstractList(const AbstractList& other);
        AbstractList& operator = (const AbstractList& other);
    };
  }
}

#endif /* _SK_UTIL_ABSTRACTLIST_ */
