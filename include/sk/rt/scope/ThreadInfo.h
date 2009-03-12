/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SCOPE_THREADINFO_H_
#define _SK_RT_SCOPE_THREADINFO_H_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace scope {
      class ThreadInfo 
        : public virtual sk::util::Object
      {
        public:
          virtual uint64_t currentThreadId() const = 0;
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_THREADINFO_H_ */
