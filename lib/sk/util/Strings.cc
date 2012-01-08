/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Items.cxx>
#include <sk/util/Strings.h>
#include <sk/util/mapper/Inspecting.hxx>

template class sk::util::Items<sk::util::String>;

sk::util::Strings::
Strings()
{
}

sk::util::Strings::
Strings(const Strings& other)
  : super_t(other)
{
}

sk::util::Strings::
Strings(const super_t& other)
  : super_t(other)
{
}

sk::util::Strings::
Strings(const sk::util::String& item)
  : super_t(item)
{
}

sk::util::Strings::
Strings(const char* item)
  : super_t(item)
{
}

const sk::util::Class
sk::util::Strings::
getClass() const
{
  return sk::util::Class("sk::util::Strings");
}
