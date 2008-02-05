/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_NAMEDSTREAMOPENER_
#define _SK_RT_CONFIG_NAMEDSTREAMOPENER_

#include <sk/util/Object.h>
#include <istream>

namespace sk {
  namespace rt {
    namespace config {
      class NamedStreamOpener
        : public virtual sk::util::Object 
      {
        public:
          // Not using std::auto_ptr<std::istream> here as it caused gcc-3.4.3
          // bug on HP-UX 11.00.PA and HP-UX 11.23.PA (works on HP-UX 11.23.IA64).
          virtual std::istream* openStream(const sk::util::String& name) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_NAMEDSTREAMOPENER_ */
