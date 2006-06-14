/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_LIST_
#define _SK_UTIL_LIST_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class List
      : public virtual sk::util::Object 
    {
      public:
        List();
        virtual ~List();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        List(const List& other);
        List& operator = (const List& other);
    };
  }
}

#endif /* _SK_UTIL_LIST_ */
