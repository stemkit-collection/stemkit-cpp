/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/Pathname.h>

sk::util::Pathname::
Pathname(const sk::util::String& component)
{
  normalizePrepended(component);
}

sk::util::Pathname::
Pathname(const sk::util::String& component, const sk::util::String& defaultExtension)
{
  normalizePrepended(component);
  if(extension().isEmpty() == true) {
    _pathname = _pathname + '.' + defaultExtension.trim();
  }
}

sk::util::Pathname::
~Pathname()
{
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
  return _location + _pathname;
}

sk::util::Pathname&
sk::util::Pathname::
front(const sk::util::String& component)
{
  normalizePrepended(component);
  return *this;
}

void
sk::util::Pathname::
normalizePrepended(const sk::util::String& component)
{
  if(isAbsolute() == true) {
    return;
  }
  sk::util::String working = component.trim();
  if(working.isEmpty() == false) {
    working = working.replace('\\', '/').squeeze('/');
    std::string::size_type position = working.find_first_of(":/");
    if(position != std::string::npos) {
      if(working[position] == ':') {
        position = working.find_first_not_of(':', position);
        _location = sk::util::String(working.substr(0, position)).trim().squeeze(':');
        if(_location.size() == 1) {
          _location.clear();
        }
        working = working.substring(position + 1).trim();
        position = working.find_first_of('/');
      }
      if(position == 0) {
        working = working.substring(1);
        _location += '/';
      }
    }
    _pathname = (_pathname.isEmpty() ? working : working + '/' + _pathname).squeeze('/');
  }
}

namespace {
  const sk::util::String figure_extension(const sk::util::String& pathname) {
    int slash = pathname.lastIndexOf('/');
    int dot = pathname.lastIndexOf('.');

    if(dot > slash) {
      return pathname.substring(dot);
    }
    return "";
  }
}

const sk::util::String
sk::util::Pathname::
extension() const
{
  return figure_extension(_pathname);
}

const sk::util::String
sk::util::Pathname::
basename() const
{
  int slash = _pathname.lastIndexOf('/');
  return slash < 0 ? _pathname : _pathname.substring(slash + 1);
}

const sk::util::String
sk::util::Pathname::
dirname() const
{
  int slash = _pathname.lastIndexOf('/');
  if(slash > 0) {
    return _location + _pathname.substring(0, slash);
  }
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
  return isAbsolute() || _pathname.equals(".") || _pathname.equals("..") || _pathname.startsWith("./") || _pathname.startsWith("../");
}
