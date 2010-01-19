/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_VALIDATOR_H_
#define _SK_UTIL_VALIDATOR_H_

#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Validator 
    {
      public:
        inline static void ensureIndex(int index, int size) {
          if((index < 0) || (index >= size)) {
            throw sk::util::IndexOutOfBoundsException("index=" + sk::util::String::valueOf(index) + ", size=" + sk::util::String::valueOf(size));
          }
        }

        inline static void ensureNotEmpty(int size) {
          ensureElement(size != 0);
        }

        inline static void ensureElement(bool condition) {
          if(condition == false) {
            throw sk::util::NoSuchElementException("ensureCondition()");
          }
        }

      private:
        Validator();
    };
  }
}

#endif /* _SK_UTIL_VALIDATOR_H_ */
