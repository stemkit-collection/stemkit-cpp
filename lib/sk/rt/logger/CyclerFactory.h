/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_LOGGER_CYCLERFACTORY_H_
#define _SK_RT_LOGGER_CYCLERFACTORY_H_

#include <sk/util/Pathname.h>
#include <sk/util/String.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace logger {
      class Cycler;

      class CyclerFactory
      {
        public:
          static sk::util::Holder<Cycler>::Sharing create(const sk::util::Pathname& pathname, const sk::util::String& policy);
          
        private:
          CyclerFactory();
          CyclerFactory(const CyclerFactory& other);
          CyclerFactory& operator = (const CyclerFactory& other);
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CYCLERFACTORY_H_ */
