/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_MIXIN_REFERENCECOUNTER_
#define _SK_UTIL_SLOT_MIXIN_REFERENCECOUNTER_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace slot {
      namespace mixin {
        class ReferenceCounter {
          public:
            ReferenceCounter() 
              : _counter(0) {}

            bool increase() {
              return _counter++ == 0;
            }
            
            bool decrease() {
              return _counter > 0 ? --_counter == 0 : true;
            }
          private:
            int _counter;
        };
      }
    }
  }
}

#endif /* _SK_UTIL_SLOT_MIXIN_REFERENCECOUNTER_ */
