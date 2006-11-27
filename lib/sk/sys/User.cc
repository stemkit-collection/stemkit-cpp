/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>
#include <sk/sys/PtyProcess.h>
#include <sk/io/IOException.h>

#include <sk/sys/User.h>
#include <pwd.h>
#include <sys/types.h>

#include <iostream>

sk::sys::User::
User(const struct passwd& entry)
  : _name(entry.pw_name), _uid(entry.pw_uid), _gid(entry.pw_gid), _home(entry.pw_dir), _shell(entry.pw_shell), _comment(entry.pw_gecos)
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
  return sk::util::Class("sk::sys::User");
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

int
sk::sys::User::
getUid() const
{
  return _uid;
}

int 
sk::sys::User::
getGid() const
{
  return _gid;
}

bool
sk::sys::User::
authenticate(const sk::util::String& password) const 
{
  sk::sys::PtyProcess process(sk::util::StringArray("su") + getName() + "-c" + "true");

  while(true) {
    char c = process.inputStream().read();
    if(c == ':') {
      break;
    }
  }
  process.outputStream().write(sk::util::Container(password + "\n"));

  try {
    while(true) {
      process.inputStream().read();
    }
  }
  catch(const sk::io::IOException& exception) {}
  process.join();

  return process.isSuccess();
}

namespace {
  struct NameComparator : public virtual sk::util::Processor<const sk::sys::User> {
    NameComparator(const sk::util::String& name, sk::util::Holder<sk::sys::User>& holder)
      : _name(name), _holder(holder) {}

    void process(const sk::sys::User& user) const {
      if(user.getName() == _name) {
        _holder.set(new sk::sys::User(user));
      }
    }
    const sk::util::String& _name;
    sk::util::Holder<sk::sys::User>& _holder;
  };
}

bool
sk::sys::User::
find(const sk::util::String& name, sk::util::Holder<sk::sys::User>& holder)
{
  forEach(NameComparator(name, holder));
  return holder.isEmpty() == false;
}

void
sk::sys::User::
forEach(const sk::util::Processor<const sk::sys::User>& processor)
{
  setpwent();
  try {
    while(true) {
      struct passwd* entry = getpwent();
      if(entry == 0) {
        break;
      }
      processor.process(sk::sys::User(*entry));
    }
  }
  catch(...) {
    endpwent();
    throw;
  }
  endpwent();
}
