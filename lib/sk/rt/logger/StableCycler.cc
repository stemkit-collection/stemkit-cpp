/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "StableCycler.h"

sk::rt::logger::StableCycler::
StableCycler()
{
}

sk::rt::logger::StableCycler::
~StableCycler()
{
}

const sk::util::Class
sk::rt::logger::StableCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::StableCycler");
}
