/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_XMLCONFIGLOADER_
#define _SK_RT_SCOPE_XMLCONFIGLOADER_

#include <sk/util/Strings.h>
#include <sk/rt/config/StreamProcessor.h>
#include <map>

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;

      class XmlConfigLoader
        : public virtual config::StreamProcessor
      {
        public:
          XmlConfigLoader(const sk::util::Strings& top, scope::Aggregator& aggregator, const std::map<std::string, std::string>& values);
          virtual ~XmlConfigLoader();

          void process(std::istream& stream, const sk::util::Pathname& location) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          XmlConfigLoader& operator = (const XmlConfigLoader& other);

          scope::Aggregator& _aggregator;
          const sk::util::Strings _top;
          const std::map<std::string, std::string> _values;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_XMLCONFIGLOADER_ */
