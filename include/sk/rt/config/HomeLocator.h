/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_HOMELOCATOR_
#define _SK_RT_CONFIG_HOMELOCATOR_

#include <sk/rt/config/SpotLocator.h>

namespace sk {
  namespace rt {
    namespace config {
      class HomeLocator
        : public SpotLocator
      {
        public:
          HomeLocator(const sk::util::String& item, const SpotLocator& other);
          HomeLocator(const sk::util::String& item);
          virtual ~HomeLocator();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          HomeLocator(const HomeLocator& other);
          HomeLocator& operator = (const HomeLocator& other);

          static const sk::util::String figureHomeLocation();
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_HOMELOCATOR_ */
