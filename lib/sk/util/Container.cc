/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/Container.h>
#include <sk/util/inspect.h>
#include <algorithm>
#include <string.h>

sk::util::Container::
Container()
{
}

sk::util::Container::
Container(const std::string& string)
  : std::vector<char>(string.begin(), string.end())
{
}

sk::util::Container::
Container(const char* buffer)
  : std::vector<char>(buffer, buffer + strlen(buffer))
{
}

sk::util::Container::
Container(const char* buffer, int length)
  : std::vector<char>(buffer, (buffer ? buffer + (length<0 ? 0 : length) : 0))
{
}

sk::util::Container::
Container(const std::string& string, int number)
  : std::vector<char>(string.begin(), string.begin() + std::min(std::max(0, number), int(string.size())))
{
}

sk::util::Container::
Container(int size)
  : std::vector<char>(size, '\0')
{
}

sk::util::Container::
Container(const std::vector<char>& vector)
  : std::vector<char>(vector)
{
}

sk::util::Container::
~Container()
{
}

const sk::util::Class
sk::util::Container::
getClass() const
{
  return sk::util::Class("sk::util::Container");
}

const sk::util::String
sk::util::Container::
inspect() const
{
  return sk::util::inspect(*this);
}

const sk::util::String
sk::util::Container::
toString() const
{
  return getChars();
}

int
sk::util::Container::
size() const
{
  return std::vector<char>::size();
}

int
sk::util::Container::
length() const
{
  return size();
}

bool
sk::util::Container::
isEmpty() const
{
  return empty();
}

sk::util::Container& 
sk::util::Container::
operator += (const std::vector<char>& other)
{
  return append(other);
}

sk::util::Container& 
sk::util::Container::
operator += (const char* buffer)
{
  return append(Container(buffer));
}

sk::util::Container& 
sk::util::Container::
operator += (const std::string& string)
{
  return append(Container(string));
}

sk::util::Container& 
sk::util::Container::
append(const std::vector<char>& other)
{
  std::vector<char>& self = *this;
  self.insert(self.end(), other.begin(), other.end());

  return *this;
}

const char* 
sk::util::Container::
getChars() const
{
  return &front();
}
