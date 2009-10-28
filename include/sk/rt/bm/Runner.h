/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_BM_RUNNER_H_
#define _SK_RT_BM_RUNNER_H_

#include <sk/util/Object.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace bm {

      class Runner 
        : public virtual sk::util::Object
      {
        public:
          virtual void init() = 0;
          virtual void start() throw() = 0;
          virtual void report(int indent, std::ostream& stream) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_BM_RUNNER_H_ */
