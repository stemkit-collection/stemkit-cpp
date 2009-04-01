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
        String(const sk::util::String& string);
        String(const std::string& string, int size);
        virtual ~String();

        String& operator=(const sk::util::String& other);

        /// Returns true if this string is empty.
        bool isEmpty() const;

        //@{
        /// Returns size of the string in bytes.
        int size() const;
        int length() const;
        //@}

        //@{
        /// Retruns a copy of this string with whitespaces removed from the
        /// beginning and the end.
        const String trim() const;
        const String strip() const;
        //@}

        /// Returns a new string where runs of a specified characters are 
        /// replaced by a single character. 
        const String squeeze(char character) const;

        /// Returns true if this string contains the specified substring.
        bool contains(const sk::util::String& other) const;
        
        /// Returns true if this string contains the specified substring,
        /// ignoring case considerations.
        bool containsIgnoreCase(const sk::util::String& other) const;

        /// Tests if this string starts with the specified prefix.
        bool startsWith(const sk::util::String& prefix) const;

        /// Tests if this string ends with the specified suffix.
        bool endsWith(const sk::util::String& suffix) const;

        //@{
        /// Returns the index within this string of the first occurrence of
        /// the specified character or substring.
        int indexOf(char character) const;
        int indexOf(const sk::util::String& other) const;
        //@}

        //@{
        /// Returns the index within this string of the last occurrence of the
        /// specified character or substring.
        int lastIndexOf(char character) const;
        int lastIndexOf(const sk::util::String& other) const;
        //@}

        /// Returns a new string that is a substring of this string.
        const String substring(int beginIndex) const;
        
        /// Returns a new string that is a substring of this string.
        const String substring(int beginIndex, int endIndex) const;

        //@{
        /// Compares this string to the other specified string.
        bool equals(const sk::util::String& other) const;
        bool equals(const char* other) const;
        //@}

        //@{
        /// Compares this String to the other String, ignoring case considerations.
        bool equalsIgnoreCase(const sk::util::String& other) const;
        bool equalsIgnoreCase(const char* other) const;
        //@}

        /// Returns a representation of this string as a C string.
        const char* getChars() const;

        /// Returns the char value at the specified index.
        char charAt(int index) const;

        /// Converts all of the characters in this String to upper case using
        /// the rules of the default locale.
        const sk::util::String toUpperCase() const;

        /// Converts all of the characters in this String to lower case using
        /// the rules of the default locale.
        const sk::util::String toLowerCase() const;

        /// Returns a new string resulting from replacing all occurrences of
        /// oldChar in this string with newChar.
        const sk::util::String replace(char oldChar, char newChar) const;

        /// Returns the string representation of the int argument.
        static const sk::util::String valueOf(int value);

        // sk::util::Object re-implementation.
        String& self();
        const String& self() const;
        const sk::util::Class getClass() const;
        const String toString() const;
        const String inspect() const;
        String* clone() const;

        static const String EMPTY;
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
