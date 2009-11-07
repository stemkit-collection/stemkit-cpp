/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_CONFIGURATOR_H_
#define _SK_UTIL_PP_CONFIGURATOR_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace pp {
      class Configurator 
        : public virtual sk::util::Object
      {
        public:
          Configurator();
          virtual ~Configurator();

          void setCompact(bool state);
          bool isCompact() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Configurator(const Configurator& other);
          Configurator& operator = (const Configurator& other);

          bool _compact;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_CONFIGURATOR_H_ */
