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

namespace sk {
  namespace util {
    const sk::util::String inspect(const char* buffer, int size);
    const sk::util::String inspect(const char* str);

    const sk::util::String inspect(const std::string& str);
    const sk::util::String inspect(const std::vector<char>& container);

    const sk::util::String inspect(const sk::util::String& str);
    const sk::util::String inspect(const sk::util::Container& container);
    const sk::util::String inspect(const sk::util::Object& object);

    const sk::util::String inspect(int data);
    const sk::util::String inspect(char data);
    const sk::util::String inspect(bool data);
  }
}

#endif /* _SK_UTIL_INSPECT_ */
