/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_UPROOTLOCATOR_
#define _SK_RT_CONFIG_UPROOTLOCATOR_

#include <sk/rt/config/SpotLocator.h>

namespace sk {
  namespace rt {
    namespace config {
      class UprootLocator
        : public SpotLocator
      {
        public:
          UprootLocator(const sk::util::String& item, const sk::util::String& location, const SpotLocator& other);
          UprootLocator(const sk::util::String& item, const sk::util::String& location);
          virtual ~UprootLocator();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          UprootLocator& operator = (const UprootLocator& other);

          static const SpotLocator figureLocator(const sk::util::String& item, const sk::util::String& location, const SpotLocator& other);
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_UPROOTLOCATOR_ */
