/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INSPECT_
#define _SK_UTIL_INSPECT_

#include <sk/util/String.h>
#include <sk/util/Container.h>
#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace util {
    const sk::util::String inspect(const char* buffer, int size);
    const sk::util::String inspect(const char* str);

    template<typename T> const sk::util::String inspect(const std::vector<T>& container);
    template<typename T> const sk::util::String inspect(const T& data);

    template<> const sk::util::String inspect(const std::string& str);
    template<> const sk::util::String inspect(const std::vector<char>& container);

    template<> const sk::util::String inspect(const sk::util::String& str);
    template<> const sk::util::String inspect(const sk::util::Container& container);
    template<> const sk::util::String inspect(const sk::util::Object& object);

    template<> const sk::util::String inspect(const int& data);
    template<> const sk::util::String inspect(const char& data);
    template<> const sk::util::String inspect(const bool& data);
  }
}

#include <sk/util/inspect.cxx>

#endif /* _SK_UTIL_INSPECT_ */
