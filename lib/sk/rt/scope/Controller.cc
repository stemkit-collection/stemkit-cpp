/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/scope/Controller.h>

sk::rt::scope::Controller::
Controller()
{
}

sk::rt::scope::Controller::
~Controller()
{
}

const sk::util::Class
sk::rt::scope::Controller::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Controller");
}

sk::rt::scope::Agregator&
sk::rt::scope::Controller::
getAgregator() 
{
  return _agregator;
}
