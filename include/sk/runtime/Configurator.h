/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_CONFIGURATOR_
#define _SK_SYS_CONFIGURATOR_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class Configurator
      : public virtual sk::util::Object 
    {
      public:
        Configurator();
        virtual ~Configurator();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Configurator(const Configurator& other);
        Configurator& operator = (const Configurator& other);
    };
  }
}

#endif /* _SK_SYS_CONFIGURATOR_ */
