/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>
#include <sk/io/AnonymousPipe.h>
#include <sk/sys/PtyProcess.h>
#include <sk/sys/Process.h>
#include <sk/sys/AbstractProcessListener.h>
#include <sk/io/IOException.h>
#include <sk/util/MissingResourceException.h>

#include <sk/sys/User.h>
#include <iostream>

static const char* __className("sk::sys::User");

sk::sys::User::
User(const struct passwd& entry)
  : _scope(*this), _uid(0), _gid(0)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::sys::User::
~User()
{
}

const sk::util::Class
sk::sys::User::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::sys::User::
getName() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::sys::User::
getComment() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::sys::User::
getHome() const 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::sys::User::
getShell() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint32_t
sk::sys::User::
getUid() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint32_t
sk::sys::User::
getGid() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::sys::User::
authenticate(const sk::util::String& password) const 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::sys::User
sk::sys::User::
find(const sk::util::String& name)
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

bool
sk::sys::User::
find(const sk::util::String& name, sk::util::Holder<sk::sys::User>& holder)
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}

void
sk::sys::User::
forEach(const sk::util::Processor<const sk::sys::User>& processor)
{
  throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}
