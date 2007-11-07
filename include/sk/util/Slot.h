/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_
#define _SK_UTIL_SLOT_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    template<class T>
    class Slot
      : public virtual sk::util::Object 
    {
      public:
        virtual bool isOwner() const = 0;
        virtual T& get() const = 0;
        virtual T* deprive() = 0;
    };
  }
}

#endif /* _SK_UTIL_SLOT_ */
