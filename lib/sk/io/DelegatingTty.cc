/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/DelegatingTty.h>

sk::io::DelegatingTty::
DelegatingTty()
{
}

sk::io::DelegatingTty::
~DelegatingTty()
{
}

const sk::util::Class
sk::io::DelegatingTty::
getClass() const
{
  return sk::util::Class("sk::io::DelegatingTty");
}

void 
sk::io::DelegatingTty::
setLines(int lines)
{
  getTty().setLines(lines);
}

void 
sk::io::DelegatingTty::
setColumns(int columns)
{
  getTty().setColumns(columns);
}
