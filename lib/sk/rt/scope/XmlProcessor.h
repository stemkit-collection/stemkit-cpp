/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_XMLPROCESSOR_
#define _SK_RT_SCOPE_XMLPROCESSOR_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>
#include <sk/util/Strings.h>
#include <map>

class TiXmlDocument;
class TiXmlHandle;
class TiXmlElement;

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;
      class IConfig;

      class XmlProcessor
        : public virtual sk::util::Object
      {
        public:
          XmlProcessor(const std::string& xml, const sk::util::Pathname& location, scope::Aggregator& aggregator, const std::map<std::string, std::string>& values);
          virtual ~XmlProcessor();

          void start(const sk::util::Strings& top);

          const TiXmlHandle& getHandle() const;
          const sk::util::Pathname& getLocation() const;
          TiXmlElement* findScopeElement(const TiXmlHandle& handle, const sk::util::String& name = sk::util::String::EMPTY);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          XmlProcessor(const XmlProcessor& other);
          XmlProcessor& operator = (const XmlProcessor& other);

          void process(const TiXmlHandle& handle, const sk::util::String& scopeBuffer, const sk::util::Strings& array, scope::Aggregator& aggregator);
          void updateConfig(const TiXmlHandle& handle, scope::IConfig& config);
          void updateLogInfo(const TiXmlHandle& handle, scope::IConfig& config);
          void updateFileDestination(const TiXmlHandle& handle, scope::IConfig& config);
          void updateProperties(const TiXmlHandle& handle, scope::IConfig& config);

          bool attribute(TiXmlElement* element, const sk::util::String& name, bool fallback);
          const sk::util::String attribute(TiXmlElement* element, const sk::util::String& name, const sk::util::String& fallback);
          const sk::util::String attribute(TiXmlElement* element, const sk::util::String& name, const char* fallback);

          const sk::util::String expand(const sk::util::String& value);

          const sk::util::Pathname _location;
          scope::Aggregator& _aggregator;
          std::map<std::string, std::string> _values;
          sk::util::Holder<TiXmlDocument> _documentHolder;
          sk::util::Holder<TiXmlHandle> _handleHolder;
          sk::util::String _scopeBuffer;
      };
    }
  }
}

std::ostream& operator<<(std::ostream& stream, const TiXmlHandle& handle);
std::ostream& operator<<(std::ostream& stream, const TiXmlDocument& document);

#endif /* _SK_RT_SCOPE_XMLPROCESSOR_ */
