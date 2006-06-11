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

        /// Returns true if this string is empty.
        bool isEmpty() const;

        /// Returns size of the string in bytes.
        int size() const;
        int length() const;

        /// Retruns a copy of this string with whitespaces removed from the
        /// beginning and the end.
        const String trim() const;
        const String strip() const;

        /// Returns a representation of this string as a C string.
        const char* getChars() const;

        // sk::util::Object re-implementation.
        String& self();
        const String& self() const;
        const sk::util::Class getClass() const;
        const String toString() const;
        const String inspect() const;
    };
  }
}

const sk::util::String operator + (const sk::util::String& s1, const sk::util::String& s2);

const sk::util::String operator + (const sk::util::String& string, const char* buffer);
const sk::util::String operator + (const char* buffer, const sk::util::String& string);

const sk::util::String operator + (const sk::util::String& string, char character);
const sk::util::String operator + (char character, const sk::util::String& string);

const sk::util::String operator + ( const sk::util::String& s1, const std::string& s2);
const sk::util::String operator + (const std::string& s1, const sk::util::String& s2);

#endif /* _SK_UTIL_STRING_ */
