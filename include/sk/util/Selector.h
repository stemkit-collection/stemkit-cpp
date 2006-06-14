/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SELECTOR_
#define _SK_UTIL_SELECTOR_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Selector
      : public virtual sk::util::Object 
    {
      public:
        Selector();
        virtual ~Selector();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Selector(const Selector& other);
        Selector& operator = (const Selector& other);
    };
  }
}

#endif /* _SK_UTIL_SELECTOR_ */
