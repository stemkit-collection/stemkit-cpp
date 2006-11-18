/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/DelegatingExecutable.h>

#include <iostream>

sk::sys::DelegatingExecutable::
DelegatingExecutable()
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
  getExecutable().stop();
}

void 
sk::sys::DelegatingExecutable::
join()
{
  getExecutable().join();
}

bool 
sk::sys::DelegatingExecutable::
isSuccess() const
{
  return getExecutable().isSuccess();
}

bool 
sk::sys::DelegatingExecutable::
isExited() const
{
  return getExecutable().isExited();
}

bool 
sk::sys::DelegatingExecutable::
isKilled() const
{
  return getExecutable().isKilled();
}

bool 
sk::sys::DelegatingExecutable::
isAlive() const
{
  return getExecutable().isAlive();
}

int 
sk::sys::DelegatingExecutable::
exitStatus() const
{
  return getExecutable().exitStatus();
}

int 
sk::sys::DelegatingExecutable::
signal() const
{
  return getExecutable().signal();
}
