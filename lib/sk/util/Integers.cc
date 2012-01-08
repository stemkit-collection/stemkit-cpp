/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Items.cxx>
#include <sk/util/Integers.h>
#include <sk/util/mapper/Inspecting.hxx>

template class sk::util::Items<uint32_t>;

sk::util::Integers::
Integers()
{
}

sk::util::Integers::
Integers(const Integers& other)
  : super_t(other)
{
}

sk::util::Integers::
Integers(const super_t& other)
  : super_t(other)
{
}

sk::util::Integers::
Integers(const uint32_t& item)
  : super_t(item)
{
}

const sk::util::Class
sk::util::Integers::
getClass() const
{
  return sk::util::Class("sk::util::Integers");
}
