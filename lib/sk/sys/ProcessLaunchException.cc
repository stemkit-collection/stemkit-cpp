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

#include <sk/sys/ProcessLaunchException.h>

static const char* __className("sk::sys::ProcessLaunchException");

namespace {
  const sk::util::String tweak_cmdline(const sk::util::String& cmdline) {
    return cmdline.substring(cmdline.indexOf('[')).trim();
  }
}

sk::sys::ProcessLaunchException::
ProcessLaunchException(const sk::util::String& message, const sk::util::Strings& cmdline)
  : Exception(sk::util::Strings(message) << tweak_cmdline(cmdline.inspect()))
{
}

const sk::util::Class
sk::sys::ProcessLaunchException::
getClass() const
{
  return sk::util::Class(__className);
}
