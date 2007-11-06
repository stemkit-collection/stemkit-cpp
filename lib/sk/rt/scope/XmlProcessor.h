/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_XMLPROCESSOR_
#define _SK_RT_SCOPE_XMLPROCESSOR_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Holder.hxx>

class TiXmlDocument;
class TiXmlHandle;

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;

      class XmlProcessor
        : public virtual sk::util::Object 
      {
        public:
          XmlProcessor(const std::string& xml, const sk::util::String& location, scope::Aggregator& aggregator);
          virtual ~XmlProcessor();

          void processElement(const sk::util::String& top);

          const TiXmlHandle& getHandle() const;
          const sk::util::String& getLocation() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          XmlProcessor(const XmlProcessor& other);
          XmlProcessor& operator = (const XmlProcessor& other);

          const sk::util::String _location;
          scope::Aggregator& _aggregator;
          sk::util::Holder<TiXmlDocument> _documentHolder;
          sk::util::Holder<TiXmlHandle> _handleHolder;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_XMLPROCESSOR_ */
