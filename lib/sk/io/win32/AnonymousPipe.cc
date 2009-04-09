/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/SystemException.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/AnonymousPipe.h>

sk::io::AnonymousPipe::
AnonymousPipe()
  : _scope(*this)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::AnonymousPipe::
~AnonymousPipe()
{
}

const sk::util::Class
sk::io::AnonymousPipe::
getClass() const
{
  return sk::util::Class("sk::io::AnonymousPipe");
}

void
sk::io::AnonymousPipe::
resetSignals()
{
}

void
sk::io::AnonymousPipe::
ignoreSignals()
{
}
