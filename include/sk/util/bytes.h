/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_BYTES_H_
#define _SK_UTIL_BYTES_H_

#include <vector>
#include <inttypes.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class bytes
      : public std::vector<uint8_t>
    {
      public:
        bytes();
        bytes(uint8_t value);
        bytes(const std::vector<uint8_t>& other);

        const sk::util::String join(const sk::util::String& delimiter) const;
        const sk::util::String inspect() const;

        sk::util::bytes& operator << (uint8_t value);
        const sk::util::bytes operator + (uint8_t value) const;
        const sk::util::bytes operator + (const sk::util::bytes& other) const;
    };

    std::ostream& operator << (std::ostream& stream, const sk::util::bytes& items);
  }
}

#endif /* _SK_UTIL_BYTES_H_ */
