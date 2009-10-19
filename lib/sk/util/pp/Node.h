/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_NODE_H_
#define _SK_UTIL_PP_NODE_H_

#include <sk/util/Object.h>
#include <ostream>

namespace sk {
  namespace util {
    namespace pp {
      class Node 
        : public virtual sk::util::Object
      {
        public:
          virtual int startPosition() const = 0;
          virtual int endPosition() const = 0;
          virtual void output(const sk::util::String& indent, std::ostream& stream) const = 0;
          virtual bool isGonnaBreak() const = 0;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_NODE_H_ */
