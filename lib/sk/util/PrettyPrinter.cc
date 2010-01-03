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
#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>
#include <sk/util/PrettyPrinter.h>

#include "pp/PrimeNode.h"
#include "pp/Configurator.h"

static const sk::util::String __className("sk::util::PrettyPrinter");

sk::util::PrettyPrinter::
PrettyPrinter(std::ostream& stream)
  : _stream(stream), _configuratorSlot(new pp::Configurator())
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

void
sk::util::PrettyPrinter::
print(const sk::util::String& input) const
{
  sk::util::Holder<sk::util::pp::Node> nodeHolder(sk::util::pp::PrimeNode().parse(sk::util::Container(input), 0, sk::util::Container()));
  if(nodeHolder.isEmpty() == true) {
    _stream << input;
  }
  else {
    nodeHolder.get().output(_configuratorSlot.get(), "", _stream);
  }
  _stream << std::endl;
}

void
sk::util::PrettyPrinter::
setCompact(bool state) 
{
  _configuratorSlot.getMutable().setCompact(state);
}

