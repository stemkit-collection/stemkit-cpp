/*  vim: sw=2:
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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/sys/User.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <nutc.h>

namespace {
  const sk::util::String __className("sk::sys::User");
}

sk::sys::User::
User(const struct passwd& entry)
  : _scope(*this), _name(entry.pw_name), _uid(entry.pw_uid), _gid(entry.pw_gid), _home(entry.pw_dir), _shell(entry.pw_shell), _comment(entry.pw_gecos)
{
}

sk::sys::User::
~User()
{
}

const sk::util::Class
sk::sys::User::
getClass() const
{
  return __className;
}

const sk::util::String
sk::sys::User::
getName() const
{
  return _name;
}

const sk::util::String
sk::sys::User::
getComment() const
{
  return _comment;
}

const sk::util::String
sk::sys::User::
getHome() const 
{
  return _home;
}

const sk::util::String
sk::sys::User::
getShell() const
{
  return _shell;
}

uint32_t
sk::sys::User::
getUid() const
{
  return _uid;
}

uint32_t 
sk::sys::User::
getGid() const
{
  return _gid;
}

bool
sk::sys::User::
authenticate(const sk::util::String& password) const 
{
    return _NutValidatePassword(_name.getChars(), password.getChars()) == 0 ? false : true;
}

const sk::sys::User
sk::sys::User::
find(const uint32_t uid)
{
  sk::util::Holder<sk::sys::User> holder;
  if(find(uid, holder) == true) {
    return holder.get();
  }
  throw sk::util::MissingResourceException("User", sk::util::String::valueOf(uid));
}

bool
sk::sys::User::
find(const uint32_t uid, sk::util::Holder<sk::sys::User>& holder)
{
  const struct passwd* pwd = getpwuid(uid);
  if(pwd == 0) {
    return false;
  }
  holder.set(new sk::sys::User(*pwd));
  return true;
}

const sk::sys::User
sk::sys::User::
find(const sk::util::String& name)
{
  sk::util::Holder<sk::sys::User> holder;
  if(find(name, holder) == true) {
    return holder.get();
  }
  throw sk::util::MissingResourceException("User", name);
}

bool
sk::sys::User::
find(const sk::util::String& name, sk::util::Holder<sk::sys::User>& holder)
{
  const struct passwd* pwd = getpwnam(name.getChars());
  if(pwd == 0) {
    return false;
  }
  holder.set(new sk::sys::User(*pwd));
  return true;
}

void
sk::sys::User::
forEach(const sk::util::Processor<const sk::sys::User>& processor)
{
    throw sk::util::UnsupportedOperationException(SK_CLASS_METHOD);
}
