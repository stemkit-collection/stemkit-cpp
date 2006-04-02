/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRING_
#define _SK_UTIL_STRING_

#include <sk/util/Object.h>
#include <string>

namespace sk {
  namespace util {
    class String
      : public virtual sk::util::Object,
        public std::string
    {
      public:
        String();
        String(char character);
        String(const char* buffer);
        String(const char* buffer, int size);
        String(const std::string& string);
        String(const std::string& string, int size);
        virtual ~String();

        const String operator + (const char* buffer) const;
        const String operator + (const std::string& string) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_UTIL_STRING_ */
