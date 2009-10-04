/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_CONTAINER_
#define _SK_UTIL_CONTAINER_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

namespace sk {
  namespace util {
    class Container
      : public std::vector<char>,
        public virtual sk::util::Object 
    {
      public:
        Container();
        Container(int size);
        Container(const char* buffer);
        Container(const char* buffer, int length);
        Container(const std::string& string);
        Container(const std::string& string, int number);
        Container(const std::vector<char>& vector);
        Container(const std::vector<char>& vector, int number);
        virtual ~Container();

        bool isEmpty() const;
        int size() const;
        int length() const;
        const char* getChars() const;

        Container& operator += (const char* buffer);
        Container& operator += (const std::string& string);
        Container& operator += (const std::vector<char>& other);

        Container& append(const std::vector<char>& other);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
        const sk::util::String toString() const;
    };
  }
}

#endif /* _SK_UTIL_CONTAINER_ */
