/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STREAMLINER_H_
#define _SK_UTIL_STREAMLINER_H_

#include <sk/util/Object.h>
#include <ostream>

namespace sk {
  namespace util {
    class StreamLiner
    {
      public:
        StreamLiner(std::ostream& stream)
          : _stream(stream), _utilized(false) {}

        ~StreamLiner() {
          if(_utilized) {
            _stream << std::endl;
          }
        }

        template<typename T> const StreamLiner& operator<<(T object) const {
          _stream << object;
          _utilized = true;
          return *this;
        }

      private:
        std::ostream& _stream;
        mutable bool _utilized;
    };
  }
}

#endif /* _SK_UTIL_STREAMLINER_H_ */
