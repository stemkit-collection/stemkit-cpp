/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_CONTROLLER_
#define _SK_RT_SCOPE_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/rt/scope/Agregator.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;
    }
    namespace scope {
      class Controller
        : public virtual sk::util::Object
      {
        public:
          Controller();
          virtual ~Controller();

          scope::Agregator& getAgregator();
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          scope::Agregator _agregator;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_CONTROLLER_ */
