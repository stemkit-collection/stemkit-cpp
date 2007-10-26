/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/inspect.h>
#include <algorithm>

sk::util::String::
String()
{
}

sk::util::String::
String(char character)
  : std::string(&character, 1)
{
}

sk::util::String::
String(const char* buffer)
  : std::string(buffer ? buffer : "")
{
}

sk::util::String::
String(const std::string& string)
  : std::string(string)
{
}

sk::util::String::
String(const sk::util::String& string)
  : std::string(string)
{
}

sk::util::String::
String(const char* buffer, int size)
{
  int index = 0;

  while(buffer && index<size && buffer[index++] != 0);
  std::string::assign(buffer, 0, index);
}

sk::util::String::
String(const std::string& string, int size)
  : std::string(string, 0, std::min(int(strlen(string.c_str())), size))
{
}

sk::util::String::
~String()
{
}

sk::util::String::
operator const char * () const
{
  return getChars();
}

sk::util::String&
sk::util::String::
operator=(const sk::util::String& other)
{
  std::string& self = *this;
  self = other;

  return *this;
}

const sk::util::Class
sk::util::String::
getClass() const
{
  return sk::util::Class("sk::util::String");
}

const sk::util::String 
sk::util::String::
toString() const
{
  return self();
}

bool
sk::util::String::
isEmpty() const
{
  return empty();
}

int 
sk::util::String::
size() const
{
  return std::string::size();
}

int 
sk::util::String::
length() const
{
  return size();
}

const char*
sk::util::String::
getChars() const
{
  return std::string::c_str();
}

sk::util::String&
sk::util::String::
self()
{
  return *this;
}

const sk::util::String&
sk::util::String::
self() const
{
  return *this;
}

const sk::util::String
sk::util::String::
trim() const
{
  const std::string whitespace = " \t\r\n\b\f";
  std::string::size_type start = find_first_not_of(whitespace);
  if(start != std::string::npos) {
    std::string::size_type end = find_first_of(whitespace, start);
    return substr(start, end == std::string::npos ? end : end - start);
  }
  return "";
}

bool
sk::util::String::
startsWith(const sk::util::String& prefix) const
{
  if(prefix.length() > length()) {
    return false;
  }
  return std::string::compare(0, prefix.length(), prefix) == 0;
}

bool
sk::util::String::
startsWith(const char* prefix) const
{
  return startsWith(sk::util::String(prefix));
}

bool
sk::util::String::
endsWith(const sk::util::String& suffix) const
{
  int offset = length() - suffix.length();
  if(offset < 0) {
    return false;
  }
  return std::string::compare(offset, suffix.length(), suffix) == 0;
}

bool
sk::util::String::
endsWith(const char* suffix) const
{
  return endsWith(sk::util::String(suffix));
}

bool 
sk::util::String::
equals(const sk::util::String& other) const
{
  return std::string::compare(other) == 0;
}

bool 
sk::util::String::
equals(const char* other) const
{
  return equals(sk::util::String(other));
}

namespace {
  inline bool compareCharsIgnoreCase(char c1, char c2) {
    return toupper(c1) == toupper(c2);
  }
}

bool 
sk::util::String::
equalsIgnoreCase(const sk::util::String& other) const
{
  if(size() != other.size()) {
    return false;
  }
  return std::equal(begin(), end(), other.begin(), compareCharsIgnoreCase);
}

bool 
sk::util::String::
equalsIgnoreCase(const char* other) const
{
  return equalsIgnoreCase(sk::util::String(other));
}

const sk::util::String
sk::util::String::
inspect() const
{
  return sk::util::inspect(*this);
}

const sk::util::String
sk::util::String::
strip() const
{
  return trim();
}

const sk::util::String operator + (const sk::util::String& s1, const sk::util::String& s2)
{
  const std::string& string1 = s1;
  const std::string& string2 = s2;

  return string1 + string2;
}

const sk::util::String operator + (const sk::util::String& string, const char* buffer)
{
  return string + sk::util::String(buffer);
}

const sk::util::String operator + (const char* buffer, const sk::util::String& string)
{
  return sk::util::String(buffer) + string;
}

const sk::util::String operator + (const sk::util::String& string, char character)
{
  return string + sk::util::String(character);
}

const sk::util::String operator + (char character, const sk::util::String& string)
{
  return sk::util::String(character) + string;
}

const sk::util::String operator + (const std::string& s1, const sk::util::String& s2)
{
  const std::string& s = s2;
  return s1 + s;
}

const sk::util::String operator + (const sk::util::String& s1, const std::string& s2)
{
  const std::string& s = s1;
  return s + s2;
}
