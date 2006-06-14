/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ARRAYLIST_
#define _SK_UTIL_ARRAYLIST_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class ArrayList
      : public virtual sk::util::Object 
    {
      public:
        ArrayList();
        virtual ~ArrayList();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        ArrayList(const ArrayList& other);
        ArrayList& operator = (const ArrayList& other);
    };
  }
}

#endif /* _SK_UTIL_ARRAYLIST_ */
