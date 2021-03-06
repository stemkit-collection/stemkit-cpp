/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/sys/AbstractProcessListener.h>

sk::sys::AbstractProcessListener::
AbstractProcessListener()
{
}

sk::sys::AbstractProcessListener::
~AbstractProcessListener()
{
}

const sk::util::Class
sk::sys::AbstractProcessListener::
getClass() const
{
  return sk::util::Class("sk::sys::AbstractProcessListener");
}

void
sk::sys::AbstractProcessListener::
processStarting(sk::io::Stream& umbilical)
{
  umbilical.close();
}

void
sk::sys::AbstractProcessListener::
processStopping()
{
}

void
sk::sys::AbstractProcessListener::
processJoining()
{
}

void
sk::sys::AbstractProcessListener::
processFailing(const sk::util::String& message)
{
}

void
sk::sys::AbstractProcessListener::
processConfiguring(sk::sys::ProcessConfigurator& configurator)
{
}
