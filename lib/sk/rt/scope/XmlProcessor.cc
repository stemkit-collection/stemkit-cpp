/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include "XmlProcessor.h"
#include <other/tinyxml/tinyxml.h>

sk::rt::scope::XmlProcessor::
XmlProcessor(const std::string& xml, const sk::util::String& location, scope::Aggregator& aggregator)
  : _location(location), _aggregator(aggregator), _documentHolder(new TiXmlDocument)
{
  _documentHolder.get().Parse(xml.c_str());
  _handleHolder.set(new TiXmlHandle(&_documentHolder.get()));
}

sk::rt::scope::XmlProcessor::
~XmlProcessor()
{
}

const sk::util::Class
sk::rt::scope::XmlProcessor::
getClass() const
{
  return sk::util::Class("sk::rt::scope::XmlProcessor");
}

const TiXmlHandle&
sk::rt::scope::XmlProcessor::
getHandle() const
{
  return _handleHolder.get();
}

const sk::util::String&
sk::rt::scope::XmlProcessor::
getLocation() const
{
  return _location;
}

void
sk::rt::scope::XmlProcessor::
processElement(const sk::util::String& top)
{
}
