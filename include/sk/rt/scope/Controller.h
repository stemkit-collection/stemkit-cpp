/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_CONTROLLER_
#define _SK_RT_SCOPE_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/rt/scope/Aggregator.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;
    }
    namespace config {
      class Locator;
    }
    namespace scope {
      class Controller
        : public virtual sk::util::Object
      {
        public:
          Controller();
          virtual ~Controller();

          void loadXmlConfig(const config::Locator& locator);
          void loadXmlConfig(const sk::util::String& top, const config::Locator& locator);

          scope::Aggregator& getAggregator();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          scope::Aggregator _aggregator;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONTROLLER_ */
