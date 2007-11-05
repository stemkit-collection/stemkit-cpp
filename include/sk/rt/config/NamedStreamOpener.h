/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_NAMEDSTREAMOPENER_
#define _SK_RT_CONFIG_NAMEDSTREAMOPENER_

#include <sk/util/Object.h>
#include <memory>
#include <istream>

namespace sk {
  namespace rt {
    namespace config {
      class NamedStreamOpener
        : public virtual sk::util::Object 
      {
        public:
          virtual std::auto_ptr<std::istream> openStream(const sk::util::String& name) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_NAMEDSTREAMOPENER_ */
