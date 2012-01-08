/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ASSESSOR_H_
#define _SK_UTIL_ASSESSOR_H_

#include <sk/util/Object.h>
#include <sk/util/Selector.h>

namespace sk {
  namespace util {
    template<typename T>
    class Assessor
      : public virtual sk::util::Selector<T>
    {
      public:
        virtual bool assess(const T& object) const = 0;
    };

    template<typename T>
    class BinaryAssessor
      : public virtual sk::util::Object
    {
      public:
        virtual bool assess(const T& first, const T& second) const = 0;
    };
  }
}

#endif /* _SK_UTIL_ASSESSOR_H_ */
