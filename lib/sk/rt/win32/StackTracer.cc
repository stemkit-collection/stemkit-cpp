/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <sk/util/Holder.cxx>

#include "StackTracer.h"

#include <stdexcept>

static const sk::util::String __className("sk::rt::StackTracer");

sk::rt::StackTracer::
StackTracer()
{
}

sk::rt::StackTracer::
~StackTracer()
{
}

const sk::util::Class
sk::rt::StackTracer::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  void generate_unsupported_error() {
    throw std::domain_error("Stack trace report not supported on Windows");
  }
}

void
sk::rt::StackTracer::
setup()
{
  generate_unsupported_error();
}

void
sk::rt::StackTracer::
finalizeFor(const sk::util::String& scope)
{
  generate_unsupported_error();
}

void
sk::rt::StackTracer::
reset()
{
  generate_unsupported_error();
}

const sk::util::String
sk::rt::StackTracer::
produceTrace()
{
  generate_unsupported_error();
  return sk::util::String::EMPTY;
}

