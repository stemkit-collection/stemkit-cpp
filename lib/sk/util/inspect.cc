/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>

#include <sk/util/inspect.h>

#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>

namespace {
  struct Converter : public std::unary_function<char, void> {
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
        default: {
          if(!(character&0x80) && isprint(character)) {
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

const sk::util::String 
sk::util::inspect(const char* buffer, int size)
{
  if(buffer == 0) {
    return "<null>";
  }
  std::ostringstream stream;
  Converter converter(stream);

  stream << "\"";
  for(int index=0; index<size ;index++) {
    converter(buffer[index]);
  }
  stream << "\"";
  return stream.str();
}

const sk::util::String 
sk::util::inspect(const char* str)
{
  if(str == 0) {
    return "<null>";
  }
  return inspect(str, strlen(str));
}

template<>
const sk::util::String 
sk::util::inspect(const std::string& str)
{
  return inspect(str.c_str(), str.size());
}

template<>
const sk::util::String 
sk::util::inspect(const std::vector<char>& container)
{
  return inspect(&container.front(), container.size());
}

template<>
const sk::util::String 
sk::util::inspect(const sk::util::String& str)
{
  return inspect(str.getChars(), str.size());
}

template<>
const sk::util::String 
sk::util::inspect(const sk::util::Container& container)
{
  return inspect(container.getChars(), container.size());
}

template<>
const sk::util::String 
sk::util::inspect(const sk::util::Object& object)
{
  return object.inspect();
}

template<>
const sk::util::String 
sk::util::inspect(const int& data)
{
  return sk::util::String::valueOf(data);
}

template<>
const sk::util::String 
sk::util::inspect(const char& data)
{
  return inspect(&data, 1).replace("\"", "'");
}

template<>
const sk::util::String 
sk::util::inspect(const bool& data)
{
  return sk::util::Boolean::toString(data);
}
