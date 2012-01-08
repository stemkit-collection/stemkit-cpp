/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_CWDUPROOTLOCATOR_
#define _SK_RT_CONFIG_CWDUPROOTLOCATOR_

#include <sk/rt/config/UprootLocator.h>

namespace sk {
  namespace rt {
    namespace config {
      class CwdUprootLocator
        : public UprootLocator
      {
        public:
          CwdUprootLocator(const sk::util::String& item, const SpotLocator& other);
          CwdUprootLocator(const sk::util::String& item);
          virtual ~CwdUprootLocator();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          CwdUprootLocator& operator = (const CwdUprootLocator& other);
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_CWDUPROOTLOCATOR_ */
