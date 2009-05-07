/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/Process.h>
#include <sk/sys/StreamPortal.h>
#include <sk/rt/Environment.h>

sk::sys::StreamPortal&
sk::sys::Process::
streamPortal()
{
  static sk::rt::Environment environment;
  static sk::sys::StreamPortal portal(environment);

  return portal;
}
