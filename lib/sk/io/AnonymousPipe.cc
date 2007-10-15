/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/SystemException.h>

#include <sk/io/AnonymousPipe.h>

#include <unistd.h>

sk::io::AnonymousPipe::
AnonymousPipe()
  : _logger(*this)
{
  int fds[2];
  
  if(::pipe(fds) < 0) {
    throw sk::util::SystemException("pipe()");
  }

  setInputFileDescriptor(fds[0]);
  setOutputFileDescriptor(fds[1]);
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
