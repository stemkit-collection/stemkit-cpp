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
#include <sk/io/AnonymousPipe.h>
#include <sk/sys/PtyProcess.h>
#include <sk/sys/Process.h>
#include <sk/sys/AbstractProcessListener.h>
#include <sk/io/IOException.h>
#include <sk/util/MissingResourceException.h>

#include <sk/sys/User.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

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


namespace {
  struct Authenticator : public sk::sys::AbstractProcessListener {
    Authenticator(const sk::sys::User& user, const sk::util::String& password)
      : _user(user), _password(password) {}

    void processStarting(sk::io::Stream& umbilical) {
      // This is needed to be able to open a pty when EUID != UID. Without it 
      // opening of a pty slave device fails on AIX.
      //
      umbilical.close();
      seteuid(getuid());
      
      // The following "trick" of keeping at least 3 file descriptors open before
      // using PtyProcess is needed for the case may 0, 1 or 2 be closed for some 
      // reason.
      //
      sk::io::AnonymousPipe p1;
      sk::io::AnonymousPipe p2;

      sk::sys::PtyProcess process(sk::util::Strings("su") + _user.getName() + "-c" + "true");

      while(true) {
        char c = process.inputStream().read();
        if(c == ':') {
          break;
        }
      }
      sleep(1);
      process.outputStream().write(sk::util::Container(_password + "\n"));

      try {
        while(true) {
          process.inputStream().read();
        }
      }
      catch(const sk::io::IOException& exception) {}
      process.join();

      _exit(process.isSuccess() ? 0: 1);
    }
    const sk::sys::User& _user;
    const sk::util::String& _password;
  };
}

bool
sk::sys::User::
authenticate(const sk::util::String& password) const 
{
  const sk::rt::Scope& scope = _scope.scope(__FUNCTION__);

  Authenticator authenticator(*this, password);
  sk::sys::Process process(authenticator);
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

const sk::sys::User
sk::sys::User::
find(const sk::util::String& name)
{
  sk::util::Holder<sk::sys::User> holder;
  if(find(name, holder) == true) {
    return holder.get();
  }
  throw sk::util::MissingResourceException(name);
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
