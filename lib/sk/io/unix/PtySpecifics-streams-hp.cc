/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PtySpecifics.h"
#include "PtyStream.h"

void
sk::io::PtySpecifics::
setup()
{
  PtyStream stream(*this);

  stream.push("ptem");
  stream.push("ldterm");
}
