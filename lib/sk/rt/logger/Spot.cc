/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Spot.h>

const sk::rt::logger::Spot sk::rt::logger::Spot::UNKNOWN;
const sk::rt::logger::Spot sk::rt::logger::Spot::NOTSET;

sk::rt::logger::Spot::
Spot()
{
}

sk::rt::logger::Spot::
~Spot()
{
}

const sk::util::Class
sk::rt::logger::Spot::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Spot");
}
