/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_AGGREGATOR_
#define _SK_RT_SCOPE_AGGREGATOR_

#include <sk/util/Object.h>
#include <sk/rt/scope/Config.h>
#include <map>

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator
        : public virtual sk::util::Object 
      {
        public:
          Aggregator();
          Aggregator(const Aggregator& other);
          virtual ~Aggregator();
          
          Config& getConfig() const;
          Aggregator& obtain(const sk::util::String& name);
          int size() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Aggregator& operator = (const Aggregator& other);

          sk::util::Holder<sk::util::Holder<Config> > _configHolderHolder;
          typedef std::map<sk::util::String, Aggregator> registry;
          registry _subordinates;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_AGGREGATOR_ */
