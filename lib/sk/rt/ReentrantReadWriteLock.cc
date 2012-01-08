/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/rt/ReentrantReadWriteLock.h>

static const sk::util::String __className("sk::rt::ReentrantReadWriteLock");

sk::rt::ReentrantReadWriteLock::
ReentrantReadWriteLock()
{
}

sk::rt::ReentrantReadWriteLock::
~ReentrantReadWriteLock()
{
}

const sk::util::Class
sk::rt::ReentrantReadWriteLock::
getClass() const
{
  return sk::util::Class(__className);
}

sk::rt::Lock&
sk::rt::ReentrantReadWriteLock::
readLock()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::rt::Lock&
sk::rt::ReentrantReadWriteLock::
writeLock()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
