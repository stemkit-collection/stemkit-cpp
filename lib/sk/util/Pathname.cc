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
  return _pathname;
}

sk::util::Pathname&
sk::util::Pathname::
front(const sk::util::String& component)
{
  if(isAbsolute() == false) {
    normalizePrepended(component);
  }
  return *this;
}

void
sk::util::Pathname::
normalizePrepended(const sk::util::String& component)
{
  const sk::util::String trimmedComponent = component.trim().replace('\\', '/');
  if(trimmedComponent.isEmpty() == false) {
    _pathname = (_pathname.isEmpty() ? trimmedComponent : trimmedComponent + '/' + _pathname).squeeze('/');
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
  return slash < 0 ? "." : _pathname.substring(0, slash);
}

bool
sk::util::Pathname::
isAbsolute() const
{
  return _pathname.startsWith('/') || (_pathname.length()>1 && _pathname.charAt(1) == ':');
}

bool
sk::util::Pathname::
isExplicit() const
{
  return isAbsolute() || _pathname.equals(".") || _pathname.equals("..") || _pathname.startsWith("./") || _pathname.startsWith("../");
}
