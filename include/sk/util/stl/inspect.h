/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STL_INSPECT_H_
#define _SK_UTIL_STL_INSPECT_H_

#include <sk/util/String.h>
#include <vector>
#include <deque>
#include <list>

namespace sk {
  namespace util {
    template<typename T> const sk::util::String inspect(const std::vector<T>& container);
    template<typename T> const sk::util::String inspect(const std::deque<T>& container);
    template<typename T> const sk::util::String inspect(const std::list<T>& container);
  }
}

#include <sk/util/stl/inspect.cxx>

#endif /* _SK_UTIL_STL_INSPECT_H_ */
