/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_UPCAST_HXX_
#define _SK_UTIL_UPCAST_HXX_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    template<typename U, typename T>
    const U& upcast(const T& object, const sk::util::String& name);

    template<typename U, typename T>
    U& upcast(T& object, const sk::util::String& name);

    template<typename U>
    const U& upcast(const sk::util::Object& object);

    template<typename U>
    U& upcast(sk::util::Object& object);
  }
}

#endif /* _SK_UTIL_UPCAST_HXX_ */
