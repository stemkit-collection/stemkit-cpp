/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/CappedStrings.h>
#include <sk/util/Injector.cxx>
#include <sk/util/reducer/Max.hxx>
#include <sk/util/mapper/Sizing.hxx>

static const sk::util::String __className("sk::util::CappedStrings");

sk::util::CappedStrings::
CappedStrings(int cap)
  : _cap(std::max(0, cap))
{
}

sk::util::CappedStrings::
CappedStrings()
  : _cap(0)
{
}

sk::util::CappedStrings::
~CappedStrings()
{
}

const sk::util::Class
sk::util::CappedStrings::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::util::CappedStrings::
maxItemSize() const
{
  return _cap > 0 ? _cap : sk::util::Injector<sk::util::String, int>(*this).inject(
    sk::util::mapper::Sizing<sk::util::String>(), sk::util::reducer::Max<sk::util::String, int>()
  );
}

bool 
sk::util::CappedStrings::
add(const sk::util::String& item)
{
  return sk::util::Strings::add(ensureCap(item));
}

bool 
sk::util::CappedStrings::
add(sk::util::String& item)
{
  return sk::util::Strings::add(ensureCap(item));
}

void 
sk::util::CappedStrings::
addFirst(const sk::util::String& item)
{
  sk::util::Strings::addFirst(ensureCap(item));
}

void 
sk::util::CappedStrings::
addFirst(sk::util::String& item)
{
  sk::util::Strings::addFirst(ensureCap(item));
}

void 
sk::util::CappedStrings::
addLast(const sk::util::String& item)
{
  sk::util::Strings::addLast(ensureCap(item));
}

void 
sk::util::CappedStrings::
addLast(sk::util::String& item)
{
  sk::util::Strings::addLast(ensureCap(item));
}

void 
sk::util::CappedStrings::
add(int index, const sk::util::String& item)
{
  sk::util::Strings::add(index, ensureCap(item));
}

void 
sk::util::CappedStrings::
add(int index, sk::util::String& item)
{
  sk::util::Strings::add(index, ensureCap(item));
}

void 
sk::util::CappedStrings::
set(int index, const sk::util::String& item)
{
  sk::util::Strings::set(index, ensureCap(item));
}

void 
sk::util::CappedStrings::
set(int index, sk::util::String& item)
{
  sk::util::Strings::set(index, ensureCap(item));
}

const sk::util::String
sk::util::CappedStrings::
ensureCap(const sk::util::String& item)
{
  if(_cap > 0) {
    int size = item.size();
    if(size > _cap) {
      return sk::util::String(item, _cap);
    }
  }
  return item;
}
