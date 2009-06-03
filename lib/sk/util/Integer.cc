/*  vi: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/NumberFormatException.h>
#include <strings.h>

#include <sstream>
#include <iomanip>

sk::util::Integer::
Integer(int value)
  : _value(value)
{
}

sk::util::Integer::
~Integer()
{
}

const sk::util::Class
sk::util::Integer::
getClass() const
{
  return sk::util::Class("sk::util::Integer");
}

const sk::util::String
sk::util::Integer::
toString() const 
{
  return sk::util::Integer::toString(_value);
}

const sk::util::String
sk::util::Integer::
inspect() const 
{
  return toString();
}

char 
sk::util::Integer::
byteValue() const
{
  return _value;
}

int 
sk::util::Integer::
intValue() const
{
  return _value;
}

short 
sk::util::Integer::
shortValue() const
{
  return _value;
}

int64_t 
sk::util::Integer::
longValue() const
{
  return _value;
}

float 
sk::util::Integer::
floatValue() const
{
  return _value;
}

double 
sk::util::Integer::
doubleValue() const
{
  return _value;
}

const sk::util::String
sk::util::Integer::
toString(int value)
{
  return toString(value, 10);
}

const sk::util::String
sk::util::Integer::
toString(int value, int radix)
{
  std::stringstream stream;
  stream << std::setbase(radix) << value;

  return stream.str();
}

namespace {
  inline int make_power(int value, int power) {
    if(power <= 0) {
      return 1;
    }
    return value * make_power(value, power - 1);
  }

  int parse(const char* value, int size, int index, int radix) {
    if(index == size) {
      return 0;
    }
    int digit = tolower(value[index]);
    if(digit >= '0' && digit <= '9') {
      digit -= '0';
    }
    else if(digit >= 'a' && digit <= 'z') {
      digit = digit - 'a' + 10;
    }
    else {
      throw sk::util::NumberFormatException("Wrong digit");
    }
    if(digit >= radix) {
      throw sk::util::NumberFormatException("Digit too big for radix");
    }
    return (digit * make_power(radix, size - index - 1)) + parse(value, size, index + 1, radix);
  }
}

int
sk::util::Integer::
parseInt(const sk::util::String& value, int radix) 
{
  return parse(value.getChars(), value.size(), 0, radix);
}

int 
sk::util::Integer::
parseInt(const sk::util::String& value)
{
  const char* buffer = value.getChars();
  int size = value.size();
  int multiplier = 1;
  int base = 10;

  if(strncasecmp("0x", buffer, 2) == 0) {
    buffer += 2;
    size -= 2;
    base = 16;
  }
  else if(strncasecmp("0b", buffer, 2) == 0) {
    buffer += 2;
    size -= 2;
    base = 2;
  }
  else if(*buffer == '0') {
    buffer += 1;
    size -= 1;
    base = 8;
  }

  if(size) {
    if(strncasecmp("M", buffer + size - 1, 1) == 0) {
      multiplier = 1024 * 1024;
      size -= 1;
    }
    else if(strncasecmp("K", buffer + size - 1, 1) == 0) {
      multiplier = 1024;
      size -= 1;
    }
  }
  return parse(buffer, size, 0, base) * multiplier;
}
