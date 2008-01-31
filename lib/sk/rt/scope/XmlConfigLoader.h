/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_XMLCONFIGLOADER_
#define _SK_RT_SCOPE_XMLCONFIGLOADER_

#include <sk/rt/config/StreamProcessor.h>
#include <sk/util/StringHash.h>

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;

      class XmlConfigLoader
        : public virtual config::StreamProcessor
      {
        public:
          XmlConfigLoader(const sk::util::String& top, scope::Aggregator& aggregator, const sk::util::StringHash& values);
          virtual ~XmlConfigLoader();

          void process(std::istream& stream, const sk::util::String& location) const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          XmlConfigLoader& operator = (const XmlConfigLoader& other);

          scope::Aggregator& _aggregator;
          const sk::util::String _top;
          const sk::util::StringHash _values;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_XMLCONFIGLOADER_ */
