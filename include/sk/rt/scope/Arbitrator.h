/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_SCOPE_ARBITRATOR_H_
#define _SK_RT_SCOPE_ARBITRATOR_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace scope {
      class Arbitrator 
        : public virtual sk::util::Object
      {
        public:
          virtual void lock() = 0;
          virtual void unlock() = 0;
          virtual bool threadInfoAvailable() const = 0;
          virtual uint64_t currentThreadId() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_ARBITRATOR_H_ */
