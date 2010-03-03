/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRINGS_H_
#define _SK_UTIL_STRINGS_H_

#include <sk/util/Items.hxx>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Strings
      : public sk::util::Items<sk::util::String>
    {
      typedef sk::util::Items<sk::util::String> super_t;
      public:
        Strings();
        Strings(const Strings& other);
        Strings(const super_t& other);

        explicit Strings(const sk::util::String& item);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_STRINGS_H_ */
