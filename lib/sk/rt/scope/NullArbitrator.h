/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SCOPE_NULLARBITRATOR_H_
#define _SK_RT_SCOPE_NULLARBITRATOR_H_

#include <sk/rt/scope/Arbitrator.h>

namespace sk {
  namespace rt {
    namespace scope {
      class NullArbitrator 
        : public virtual sk::rt::scope::Arbitrator
      {
        public:
          // sk::rt::scope::Arbitrator implementation.
          inline void lock() {
          }

          inline bool tryLock() {
            return true;
          }

          inline bool isLocked() const {
            return false;
          }

          inline void unlock() {
          }

          inline void reset() {
          }

          inline uint64_t currentThreadId() const {
            return 0;
          }
      };
    }
  }
}

#endif /* _SK_RT_SCOPE_NULLARBITRATOR_H_ */
