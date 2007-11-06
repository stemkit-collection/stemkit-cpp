/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "XmlConfigLoader.h"

sk::rt::scope::XmlConfigLoader::
XmlConfigLoader(scope::Aggregator& aggregator)
  : _aggregator(aggregator)
{
}

sk::rt::scope::XmlConfigLoader::
~XmlConfigLoader()
{
}

const sk::util::Class
sk::rt::scope::XmlConfigLoader::
getClass() const
{
  return sk::util::Class("sk::rt::scope::XmlConfigLoader");
}

void
sk::rt::scope::XmlConfigLoader::
process(std::istream& stream, const sk::util::String& location) const 
{
}
