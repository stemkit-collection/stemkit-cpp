/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INTEGERS_H_
#define _SK_UTIL_INTEGERS_H_

#include <sk/util/Items.hxx>
#include <sk/util/Integer.h>

namespace sk {
  namespace util {
    class Integers
      : public sk::util::Items<uint32_t>
    {
      typedef sk::util::Items<uint32_t> super_t;
      public:
        Integers();
        Integers(const Integers& other);
        Integers(const super_t& other);
        Integers(const uint32_t& item);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_INTEGERS_H_ */
