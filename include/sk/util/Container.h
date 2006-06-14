/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_CONTAINER_
#define _SK_UTIL_CONTAINER_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Container
      : public virtual sk::util::Object 
    {
      public:
        Container();
        virtual ~Container();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Container(const Container& other);
        Container& operator = (const Container& other);
    };
  }
}

#endif /* _SK_UTIL_CONTAINER_ */
