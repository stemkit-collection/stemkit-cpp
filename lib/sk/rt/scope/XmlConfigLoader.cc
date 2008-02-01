/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "XmlConfigLoader.h"
#include "XmlProcessor.h"

#include <sstream>

sk::rt::scope::XmlConfigLoader::
XmlConfigLoader(const sk::util::String& top, scope::Aggregator& aggregator, const std::map<std::string, std::string>& values)
  : _top(top), _aggregator(aggregator), _values(values)
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
  std::string incoming;
  std::stringstream content;

  while(getline(stream, incoming).eof() == false) {
    content << incoming << std::endl;
  }
  XmlProcessor processor(content.str(), location, _aggregator, _values);
  processor.start(_top);
}
