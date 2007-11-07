/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>
#include <sk/util/Holder.cxx>

#include "XmlProcessor.h"
#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/logger/Level.h>
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
start(const sk::util::String& scope)
{
  process(findScopeElement(getHandle(), scope), _aggregator);
}

TiXmlElement*
sk::rt::scope::XmlProcessor::
findScopeElement(const TiXmlHandle& handle, const sk::util::String& name) 
{
  for(TiXmlElement* item=handle.FirstChild("scope").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    if(name.isEmpty() == true || name.equals(item->Attribute("name")) == true) {
      return item;
    }
  }
  return 0;
}

void
sk::rt::scope::XmlProcessor::
process(const TiXmlHandle& handle, scope::Aggregator& aggregator) 
{
  updateConfig(handle, aggregator.getConfigForUpdate());

  for(TiXmlElement* item=handle.FirstChild("scope").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    const sk::util::String name = sk::util::String(item->Attribute("name")).trim();
    if(name.isEmpty() == true) {
      continue;
    }
    process(item, aggregator.obtain(name));
  }
}

void
sk::rt::scope::XmlProcessor::
updateConfig(const TiXmlHandle& handle, scope::Config& config)
{
  for(TiXmlElement* item=handle.FirstChild("log").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    updateLogInfo(item, config);
  }
  updateProperties(handle, config);
}

namespace {
  bool attribute(TiXmlElement* element, const sk::util::String& name, const sk::util::Boolean& fallback) {
    if(element) {
      return sk::util::Boolean::parseBoolean(element->Attribute(name.getChars()));
    }
    return fallback.booleanValue();
  }
}

void 
sk::rt::scope::XmlProcessor::
updateLogInfo(const TiXmlHandle& handle, scope::Config& config) 
{
  config.setLogObject(attribute(handle.ToElement(), "show-object", config.isLogObject()));
  config.setLogTime(attribute(handle.ToElement(), "show-time", config.isLogTime()));
  config.setLogPid(attribute(handle.ToElement(), "show-pid", config.isLogPid()));

  for(TiXmlElement* item=handle.FirstChild("level").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    config.setLogLevel(sk::rt::logger::Level::valueOf(item->Attribute("severity")));
  }
}

void
sk::rt::scope::XmlProcessor::
updateProperties(const TiXmlHandle& handle, scope::Config& config) 
{
  for(TiXmlElement* item=handle.FirstChild("property").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    const char* value = item->Attribute("value");
    config.setProperty(item->Attribute("name"), value ? value : item->ToText()->Value());
  }
}
