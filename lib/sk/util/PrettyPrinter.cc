/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/util/PrettyPrinter.h>

static const sk::util::String __className("sk::util::PrettyPrinter");

sk::util::PrettyPrinter::
PrettyPrinter()
{
}

sk::util::PrettyPrinter::
~PrettyPrinter()
{
}

const sk::util::Class
sk::util::PrettyPrinter::
getClass() const
{
  return sk::util::Class(__className);
}
