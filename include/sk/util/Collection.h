/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_COLLECTION_
#define _SK_UTIL_COLLECTION_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Collection
      : public virtual sk::util::Object 
    {
      public:
        Collection();
        virtual ~Collection();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Collection(const Collection& other);
        Collection& operator = (const Collection& other);
    };
  }
}

#endif /* _SK_UTIL_COLLECTION_ */
