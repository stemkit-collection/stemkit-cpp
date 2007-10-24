/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_AGREGATOR_
#define _SK_RT_SCOPE_AGREGATOR_

#include <sk/util/Object.h>
#include <sk/rt/scope/Config.h>
#include <map>

namespace sk {
  namespace rt {
    namespace scope {
      class Agregator
        : public virtual sk::util::Object 
      {
        public:
          Agregator();
          Agregator(const Agregator& other);
          virtual ~Agregator();
          
          Config& getConfig() const;
          Agregator& obtain(const sk::util::String& name);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Agregator& operator = (const Agregator& other);

          sk::util::Holder<sk::util::Holder<Config> > _configHolderHolder;
          typedef std::map<sk::util::String, Agregator> registry;
          registry _subordinates;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_AGREGATOR_ */
