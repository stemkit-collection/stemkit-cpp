/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/DelegatingExecutable.h>

sk::sys::DelegatingExecutable::
DelegatingExecutable(sk::sys::Executable& executable)
  : _executable(executable)
{
}

sk::sys::DelegatingExecutable::
~DelegatingExecutable()
{
}

const sk::util::Class
sk::sys::DelegatingExecutable::
getClass() const
{
  return sk::util::Class("sk::sys::DelegatingExecutable");
}

void 
sk::sys::DelegatingExecutable::
stop()
{
  _executable.stop();
}

void 
sk::sys::DelegatingExecutable::
join()
{
  _executable.join();
}

bool 
sk::sys::DelegatingExecutable::
isSuccess() const
{
  return _executable.isSuccess();
}

bool 
sk::sys::DelegatingExecutable::
isExited() const
{
  return _executable.isExited();
}

bool 
sk::sys::DelegatingExecutable::
isKilled() const
{
  return _executable.isKilled();
}

bool 
sk::sys::DelegatingExecutable::
isAlive() const
{
  return _executable.isAlive();
}

int 
sk::sys::DelegatingExecutable::
exitStatus() const
{
  return _executable.exitStatus();
}

int 
sk::sys::DelegatingExecutable::
signal() const
{
  return _executable.signal();
}
