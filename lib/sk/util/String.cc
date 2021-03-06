/*  vim: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/inspect.h>
#include <sk/util/Strings.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalArgumentException.h>
#include <algorithm>
#include <functional>
#include <strings.h>

const sk::util::String sk::util::String::EMPTY;

namespace {
  const sk::util::String __className("sk::util::String");
  const char* __whitespace(" \t\r\n\b\f");
}

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
  if(buffer == 0) {
    return;
  }
  int index = 0;
  while(index < size && buffer[index] != 0) {
    ++index;
  }
  std::string::assign(buffer, buffer + index);
}

namespace {
  int figure_size(const char* s, int s1, int s2) {
    int index = 0;
    while((index < s1) && (index < s2) && (s[index] != 0)) {
      ++index;
    }
    return index;
  }
}

sk::util::String::
String(const std::string& string, int size)
  : std::string(string, 0, figure_size(string.c_str(), string.size(), size))
{
}

sk::util::String::
~String()
{
}

sk::util::Object*
sk::util::String::
clone() const
{
  return new String(*this);
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
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::String::
toString() const
{
  return *this;
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

const sk::util::String
sk::util::String::
trim() const
{
  const std::string::size_type start = find_first_not_of(__whitespace);
  if(start != std::string::npos) {
    const std::string::size_type end = find_last_not_of(__whitespace);
    return substr(start, end == std::string::npos ? end : end - start + 1);
  }
  return "";
}

bool
sk::util::String::
startsWith(const sk::util::String& prefix) const
{
  return indexOf(prefix) == 0;
}

bool
sk::util::String::
startsWithIgnoreCase(const sk::util::String& prefix) const
{
  return indexOfIgnoreCase(prefix) == 0;
}

bool
sk::util::String::
endsWith(const sk::util::String& suffix) const
{
  const int offset = length() - suffix.length();
  return offset >= 0 && lastIndexOf(suffix) == offset;
}

bool
sk::util::String::
endsWithIgnoreCase(const sk::util::String& suffix) const
{
  const int offset = length() - suffix.length();
  return offset >= 0 && lastIndexOfIgnoreCase(suffix) == offset;
}

bool
sk::util::String::
equals(const sk::util::String& other) const
{
  return std::string::compare(other) == 0;
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

namespace {
  struct UniqueChecker
    : public std::binary_function<char, char, bool>
  {
    UniqueChecker(char character)
      : _character(character) {}

    bool operator()(char c1, char c2) const {
      return c1 == c2 && c1 == _character;
    }
    const char _character;
  };
}

const sk::util::String
sk::util::String::
squeeze(char character) const
{
  String result;
  std::unique_copy(begin(), end(), std::back_insert_iterator<std::string>(result), UniqueChecker(character));

  return result;
}

int
sk::util::String::
indexOf(char character) const
{
  const size_type pos = std::string::find_first_of(character);
  if(pos == std::string::npos) {
    return -1;
  }
  return pos - 0;
}

int
sk::util::String::
indexOfIgnoreCase(char character) const
{
  const char targets[] = {
    toupper(character),
    tolower(character),
    0
  };
  const size_type pos = std::string::find_first_of(targets);
  if(pos == std::string::npos) {
    return -1;
  }
  return pos - 0;
}

int
sk::util::String::
lastIndexOf(char character) const
{
  const size_type pos = std::string::find_last_of(character);
  if(pos == std::string::npos) {
    return -1;
  }
  return pos - 0;
}

int
sk::util::String::
lastIndexOfIgnoreCase(char character) const
{
  const char targets[] = {
    toupper(character),
    tolower(character),
    0
  };
  const size_type pos = std::string::find_last_of(targets);
  if(pos == std::string::npos) {
    return -1;
  }
  return pos - 0;
}

const sk::util::String
sk::util::String::
substring(int beginIndex) const
{
  if(beginIndex < 0 || beginIndex > size()) {
    throw IndexOutOfBoundsException("substring()");
  }
  if(beginIndex == 0) {
    return *this;
  }
  if(beginIndex == size()) {
    return String::EMPTY;
  }
  return std::string::substr(beginIndex);
}

const sk::util::String
sk::util::String::
substring(int beginIndex, int endIndex) const
{
  if(endIndex < 0) {
    endIndex += (size() + 1);
  }
  if(beginIndex < 0 || endIndex > size() || beginIndex > endIndex) {
    throw IndexOutOfBoundsException("substring()");
  }
  if(beginIndex == 0 && endIndex == size()) {
    return *this;
  }
  if(beginIndex == endIndex) {
    return String::EMPTY;
  }
  return std::string::substr(beginIndex, endIndex - beginIndex);
}

const sk::util::String
sk::util::String::
toUpperCase() const
{
  sk::util::String result(*this);
  std::transform(result.begin(), result.end(), result.begin(), toupper);

  return result;
}

const sk::util::String
sk::util::String::
toLowerCase() const
{
  sk::util::String result(*this);
  std::transform(result.begin(), result.end(), result.begin(), tolower);

  return result;
}

char
sk::util::String::
charAt(int index) const
{
  try {
    return at(index);
  }
  catch(...) {
    throw IndexOutOfBoundsException("charAt()");
  }
}

namespace {
  struct CharReplacer {
    CharReplacer(char oldChar, char newChar)
      : _oldChar(oldChar), _newChar(newChar) {}

    char operator()(char current) {
      return current == _oldChar ? _newChar : current;
    }
    const char _oldChar;
    const char _newChar;
  };
}

const sk::util::String
sk::util::String::
replace(char oldChar, char newChar) const
{
  sk::util::String result(*this);
  std::transform(result.begin(), result.end(), result.begin(), CharReplacer(oldChar, newChar));

  return result;
}

const sk::util::String
sk::util::String::
replace(const sk::util::String& target, const sk::util::String& replacement) const
{
  std::string result(*this);

  std::string::size_type index = 0;
  while(true) {
    index = result.find(target, index);
    if(index == std::string::npos) {
      break;
    }
    result.replace(index, target.size(), replacement);
    index += replacement.size();
  }
  return result;
}

bool
sk::util::String::
contains(const sk::util::String& other) const
{
  return indexOf(other) < 0 ? false : true;
}

bool
sk::util::String::
containsIgnoreCase(const sk::util::String& other) const
{
  return indexOfIgnoreCase(other) < 0 ? false : true;
}

int
sk::util::String::
indexOf(const sk::util::String& other) const
{
  const int other_size = other.size();
  if(other_size == 0) {
    return 0;
  }
  const int delta = size() - other_size;
  for(int index=0; index <= delta ;++index) {
    if(compare(index, other_size, other) == 0) {
      return index;
    }
  }
  return -1;
}

int
sk::util::String::
indexOfIgnoreCase(const sk::util::String& other) const
{
  const int other_size = other.size();
  if(other_size == 0) {
    return 0;
  }
  const int delta = size() - other_size;
  for(int index=0; index <= delta ;++index) {
    if(std::equal(begin() + index, begin() + index + other_size, other.begin(), compareCharsIgnoreCase) == true) {
      return index;
    }
  }
  return -1;
}

int
sk::util::String::
lastIndexOf(const sk::util::String& other) const
{
  const int other_size = other.size();
  if(other_size == 0) {
    return size();
  }
  const int delta = size() - other_size;
  for(int index=delta; index >= 0 ;--index) {
    if(compare(index, other_size, other) == 0) {
      return index;
    }
  }
  return -1;
}

int
sk::util::String::
lastIndexOfIgnoreCase(const sk::util::String& other) const
{
  const int other_size = other.size();
  if(other_size == 0) {
    return 0;
  }
  const int delta = size() - other_size;
  for(int index=delta; index >= 0 ;--index) {
    if(std::equal(begin() + index, begin() + index + other_size, other.begin(), compareCharsIgnoreCase) == true) {
      return index;
    }
  }
  return -1;
}

const sk::util::String
sk::util::String::
valueOf(int value)
{
  return Integer::toString(value);
}

const sk::util::String
sk::util::String::
times(int multiplier) const
{
  if(multiplier < 0) {
    throw sk::util::IllegalArgumentException(sk::util::String::valueOf(multiplier));
  }
  if(isEmpty() || multiplier == 0) {
    return sk::util::String::EMPTY;
  }
  std::string result;
  result.reserve(length() * multiplier);
  for(int counter=multiplier; counter ;--counter) {
    result.insert(result.end(), begin(), end());
  }
  return result;
}

namespace {
  const sk::util::Strings sliceEachChar(const sk::util::String& item) {
    sk::util::Strings result;
    for(std::string::const_iterator iterator = item.begin(); iterator != item.end(); ++iterator) {
      result << sk::util::String(*iterator);
    }
    return result;
  }

  const sk::util::Strings sliceSeparator(const sk::util::String& item, const sk::util::String& separator, const bool squeeze) {
    sk::util::Strings result;
    if(item.isEmpty() == true) {
      return result;
    }
    std::string::size_type head_index = 0;
    while(true) {
      if(squeeze == true) {
        head_index = item.find_first_not_of(separator, head_index);
        if(head_index == std::string::npos) {
          break;
        }
      }
      const std::string::size_type tail_index = item.find_first_of(separator, head_index);
      if(tail_index == std::string::npos) {
        result << item.substr(head_index);
        break;
      }
      result << item.substr(head_index, tail_index - head_index);
      head_index = tail_index + 1;
    }
    return result;
  }
}

const sk::util::Strings
sk::util::String::
split(const sk::util::String& separator) const
{
  const int separator_size = separator.size();
  if(separator_size == 0) {
    return sliceEachChar(*this);
  }
  if(separator_size == 1 && separator.charAt(0) == ' ') {
    return split();
  }
  return sliceSeparator(*this, separator, false);
}

const sk::util::Strings
sk::util::String::
split() const
{
  return sliceSeparator(*this, __whitespace, true);
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

const sk::util::String operator * (const sk::util::String& string, int multiplier)
{
  return string.times(multiplier);
}

bool
sk::util::String::
operator<(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f < s;
}

bool
sk::util::String::
operator<(const std::string& other) const
{
  const std::string& f = *this;

  return f < other;
}

bool
sk::util::String::
operator<(const char* other) const
{
  const std::string& f = *this;

  return f < other;
}

bool
sk::util::String::
operator>(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f > s;
}

bool
sk::util::String::
operator>(const std::string& other) const
{
  const std::string& f = *this;

  return f > other;
}

bool
sk::util::String::
operator>(const char* other) const
{
  const std::string& f = *this;

  return f > other;
}

bool
sk::util::String::
operator==(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f == s;
}

bool
sk::util::String::
operator==(const std::string& other) const
{
  const std::string& f = *this;

  return f == other;
}

bool
sk::util::String::
operator==(const char* other) const
{
  const std::string& f = *this;

  return f == other;
}

bool
sk::util::String::
operator!=(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f != s;
}

bool
sk::util::String::
operator!=(const std::string& other) const
{
  const std::string& f = *this;

  return f != other;
}

bool
sk::util::String::
operator!=(const char* other) const
{
  const std::string& f = *this;

  return f != other;
}

bool
sk::util::String::
operator<=(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f <= s;
}

bool
sk::util::String::
operator<=(const std::string& other) const
{
  const std::string& f = *this;

  return f <= other;
}

bool
sk::util::String::
operator<=(const char* other) const
{
  const std::string& f = *this;

  return f <= other;
}

bool
sk::util::String::
operator>=(const sk::util::String& other) const
{
  const std::string& f = *this;
  const std::string& s = other;

  return f >= s;
}

bool
sk::util::String::
operator>=(const std::string& other) const
{
  const std::string& f = *this;

  return f >= other;
}

bool
sk::util::String::
operator>=(const char* other) const
{
  const std::string& f = *this;

  return f >= other;
}

std::ostream&
sk::util::operator<<(std::ostream& stream, const sk::util::String& object)
{
  const std::string s = object;
  return stream << s;
}
