/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_ICONFIG_
#define _SK_RT_SCOPE_ICONFIG_

#include <sk/rt/logger/IConfig.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>

namespace sk {
  namespace rt {
    namespace scope {
      class IConfig
        : public virtual logger::IConfig
      {
        public:
          virtual const sk::util::String getProperty(const sk::util::String& name) const = 0;
          virtual const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const = 0;
          virtual const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const = 0;
          virtual bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const = 0;
          virtual int getProperty(const sk::util::String& name, int fallback) const = 0;
          virtual bool hasProperty(const sk::util::String& name) const = 0;

          virtual void setProperty(const sk::util::String& name, const sk::util::String& value) = 0;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_ICONFIG_ */
