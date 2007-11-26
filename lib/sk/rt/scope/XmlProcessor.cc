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
#include <sk/rt/logger/ExternalStreamDestination.h>
#include <sk/rt/logger/FileDestination.h>
#include <other/tinyxml/tinyxml.h>

#include <iostream>
#include <sstream>

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

  const sk::util::String attribute(TiXmlElement* element, const sk::util::String& name, const char* fallback) {
    if(element) {
      const char* value = element->Attribute(name.getChars());
      if(value) {
        return value;
      }
    }
    return fallback;
  }
}

void 
sk::rt::scope::XmlProcessor::
updateLogInfo(const TiXmlHandle& handle, scope::Config& config) 
{
  config.setLogObject(attribute(handle.ToElement(), "show-object", config.isLogObject()));
  config.setLogTime(attribute(handle.ToElement(), "show-time", config.isLogTime()));
  config.setLogPid(attribute(handle.ToElement(), "show-pid", config.isLogPid()));

  const sk::util::String destination = attribute(handle.ToElement(), "destination", "");
  if(destination.equals("std::cout")) {
    config.setLogDestination(logger::ExternalStreamDestination(std::cout));
  }
  else if(destination.equals("std::clog")) {
    config.setLogDestination(logger::ExternalStreamDestination(std::clog));
  }
  else if(destination.equals("std::cerr")) {
    config.setLogDestination(logger::ExternalStreamDestination(std::cerr));
  }
  else {
    for(TiXmlElement* item=handle.FirstChild("file").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
      updateFileDestination(item, config);
    }
  }
  const sk::util::String level(attribute(handle.ToElement(), "level", "").trim());
  if(level.isEmpty() == false) {
    config.setLogLevel(logger::Level::valueOf(level));
  }
  for(TiXmlElement* item=handle.FirstChild("level").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    config.setLogLevel(sk::rt::logger::Level::valueOf(item->Attribute("severity")));
  }
}

namespace {
  const sk::util::String figure_text(const char* value, TiXmlNode* node) {
    if(value) {
      return value;
    }
    std::stringstream text_element_collector;
    for(TiXmlNode* item=node->FirstChild(); item ;item=item->NextSibling()) {
      if(item->Type() == TiXmlNode::TEXT) {
        text_element_collector << item->ToText()->ValueStr();
      }
    }
    return text_element_collector.str();
  }
}

void
sk::rt::scope::XmlProcessor::
updateProperties(const TiXmlHandle& handle, scope::Config& config) 
{
  for(TiXmlElement* item=handle.FirstChild("property").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    config.setProperty(item->Attribute("name"), figure_text(item->Attribute("value"), item));
  }
}

void
sk::rt::scope::XmlProcessor::
updateFileDestination(const TiXmlHandle& handle, scope::Config& config) 
{
  attribute(handle.ToElement(), "location", "");
  attribute(handle.ToElement(), "name", "");
  attribute(handle.ToElement(), "size", "");
  attribute(handle.ToElement(), "chunks", "");
}
