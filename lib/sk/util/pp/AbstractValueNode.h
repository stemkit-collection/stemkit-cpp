/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_ABSTRACTVALUENODE_H_
#define _SK_UTIL_PP_ABSTRACTVALUENODE_H_

#include "Node.h"
#include <vector>

namespace sk {
  namespace util {
    namespace pp {
      class AbstractValueNode 
        : public virtual sk::util::pp::Node
      {
        public:
          AbstractValueNode();
          AbstractValueNode(const std::vector<char>& data, int start, int end);
          virtual ~AbstractValueNode();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String toString() const;

          // sk::util::pp::Node implementation.
          int startPosition() const;
          int endPosition() const;
      
        private:
          AbstractValueNode(const AbstractValueNode& other);
          AbstractValueNode& operator = (const AbstractValueNode& other);

          const sk::util::String _value;
          int _start;
          int _end;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_ABSTRACTVALUENODE_H_ */
