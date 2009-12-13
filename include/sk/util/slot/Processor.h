/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SLOT_PROCESSOR_H_
#define _SK_UTIL_SLOT_PROCESSOR_H_

#include <sk/util/Object.h>
#include <sk/util/Slot.hxx>

namespace sk {
  namespace util {
    namespace slot {
      template<typename T>
      class Processor 
        : public virtual sk::util::Object
      {
        public:
          virtual bool process(const sk::util::Slot<T>& slot) const = 0;
      };
    }
  }
}

#endif /* _SK_UTIL_SLOT_PROCESSOR_H_ */
