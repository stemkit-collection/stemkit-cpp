/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STL_VECTORPOPULATOR_HXX_
#define _SK_UTIL_STL_VECTORPOPULATOR_HXX_

#include <sk/util/Processor.h>

namespace sk {
  namespace util {
    namespace stl {
      template<typename T>
      class VectorPopulator 
        : public virtual sk::util::Processor<const T>
      {
        public:
          VectorPopulator(std::vector<T>& destination)
            : _destination(destination) {}
      
          void process(const T& object) const {
            _destination.push_back(object);
          }
      
        private:
          std::vector<T>& _destination;
      };
    }
  }
}

#endif /* _SK_UTIL_STL_VECTORPOPULATOR_HXX_ */
