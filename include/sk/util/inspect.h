/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_INSPECT_
#define _SK_UTIL_INSPECT_

#include <sk/util/String.h>

#include <sstream>
#include <algorithm>
#include <iomanip>

namespace sk {
  namespace util {
    namespace {
      struct Converter 
        : public std::unary_function<char, void> 
      {
        Converter(std::ostream& stream) 
          : _stream(stream) {}

        void operator() (const char& character) {
          switch(character) {
            case '\r': {
              _stream << "\\r";
              break;
            }
            case '\n': {
              _stream << "\\n";
              break;
            }
            case '\t': {
              _stream << "\\t";
              break;
            }
            case '\b': {
              _stream << "\\b";
              break;
            }
            case '\f': {
              _stream << "\\f";
              break;
            }
            case '\"': {
              _stream << "\\\"";
              break;
            }
            case '\0': {
              _stream << "\\0";
              break;
            }
            default: {
              if(isprint(character)) {
                _stream << character;
              }
              else {
                _stream << "\\x" << std::hex << std::setw(2) << std::setfill('0') << std::uppercase;
                _stream << (int(character) & 0xff);
              }
              break;
            }
          }
        }
        std::ostream& _stream;
      };
    }

    template<class T>
    const sk::util::String inspect(T& container)
    {
      std::stringstream stream;
      std::for_each(container.begin(), container.end(), Converter(stream));

      return '"' + stream.str() + '"';
    }
  }
}

#endif /* _SK_UTIL_INSPECT_ */
