/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/util/Pathname.h>

sk::util::Pathname::
Pathname(const char* component)
{
  normalize(component);
}

sk::util::Pathname::
Pathname(const sk::util::String& component)
{
  normalize(component);
}

sk::util::Pathname::
Pathname(const sk::util::String& component, const sk::util::String& defaultExtension)
{
  normalize(component);
  if(extension().isEmpty() == true) {
    _path = _path + '.' + defaultExtension.trim();
  }
}

sk::util::Pathname::
~Pathname()
{
}

bool
sk::util::Pathname::
operator == (const sk::util::Pathname& other) const
{
  return _location.equals(other._location) && _path.equals(other._path);
}

bool
sk::util::Pathname::
operator != (const sk::util::Pathname& other) const
{
  return !operator==(other);
}

const sk::util::Class
sk::util::Pathname::
getClass() const
{
  return sk::util::Class("sk::util::Pathname");
}

const sk::util::String
sk::util::Pathname::
toString() const
{
  return _location + _path;
}

const sk::util::Pathname
sk::util::Pathname::
join(const sk::util::Pathname& other) const
{
  if(isEmpty() == true) {
    return other;
  }
  if(other.isEmpty() == true) {
    return *this;
  }
  if(other.isAbsolute() == true) {
    return other;
  }
  Pathname result(*this);
  if(_path.endsWith("/") == false) {
    result._path += '/';
  }
  result._path += other._path;
  return result;
}

void
sk::util::Pathname::
normalize(const sk::util::String& component)
{
  _path = component.trim();

  if(_path.isEmpty() == false) {
    _path = _path.replace('\\', '/').squeeze('/');
    std::string::size_type position = _path.find_first_of(":/");
    if(position != std::string::npos) {
      if(_path[position] == ':') {
        position = _path.find_first_not_of(':', position);
        _location = sk::util::String(_path.substr(0, position)).trim().squeeze(':');
        if(_location.size() == 1) {
          _location.clear();
        }
        if(position != std::string::npos) {
          _path = _path.substring(position).trim();
        }
        else { 
          _path.clear();
        }
        position = _path.find_first_of('/');
      }
      if(position == 0) {
        _path = _path.substring(1);
        _location += '/';
      }
    }
  }
}

namespace {
  const sk::util::String figure_extension(const sk::util::String& pathname) {
    int slash = pathname.lastIndexOf('/');
    int dot = pathname.lastIndexOf('.');

    if(dot > slash) {
      return pathname.substring(dot);
    }
    return sk::util::String::EMPTY;
  }
}

const sk::util::String
sk::util::Pathname::
extension() const
{
  return figure_extension(_path);
}

const sk::util::String
sk::util::Pathname::
basename() const
{
  int slash = _path.lastIndexOf('/');
  return slash < 0 ? _path : _path.substring(slash + 1);
}

const sk::util::Pathname
sk::util::Pathname::
dirname() const
{
  int slash = _path.lastIndexOf('/');
  if(slash > 0) {
    return _location + _path.substring(0, slash);
  }
  return location();
}

const sk::util::String
sk::util::Pathname::
location() const
{
  return _location.isEmpty() ? "." : _location;
}

bool
sk::util::Pathname::
isAbsolute() const
{
  return _location.isEmpty() == false;
}

bool
sk::util::Pathname::
isExplicit() const
{
  return isAbsolute() || _path.equals(".") || _path.equals("..") || _path.startsWith("./") || _path.startsWith("../");
}

bool
sk::util::Pathname::
isTerminal() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::util::Pathname::
isEmpty() const
{
  return _location.isEmpty() && _path.isEmpty();
}

const sk::util::Pathname operator + (const sk::util::Pathname& first, const sk::util::Pathname& second)
{
  return first.join(second);
}
