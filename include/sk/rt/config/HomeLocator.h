/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_HOMELOCATOR_
#define _SK_RT_CONFIG_HOMELOCATOR_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace config {
      class HomeLocator
        : public virtual sk::util::Object 
      {
        public:
          HomeLocator();
          virtual ~HomeLocator();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          HomeLocator(const HomeLocator& other);
          HomeLocator& operator = (const HomeLocator& other);
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_HOMELOCATOR_ */
