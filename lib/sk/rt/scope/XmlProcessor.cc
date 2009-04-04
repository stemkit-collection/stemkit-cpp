/*  vim: set sw=2:
 *
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>
#include <sk/util/Holder.cxx>
#include <sk/util/Pathname.h>

#include "XmlProcessor.h"
#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/logger/Level.h>
#include <logger/StreamDestination.h>
#include <logger/CyclerFactory.h>
#include <logger/FileDestination.h>
#include <logger/PipeDestination.h>
#include <logger/TrashDestination.h>
#include <sk/other/tinyxml/tinyxml.h>

#include <iostream>
#include <sstream>

sk::rt::scope::XmlProcessor::
XmlProcessor(const std::string& xml, const sk::util::Pathname& location, scope::Aggregator& aggregator, const std::map<std::string, std::string>& values)
  : _location(location), _aggregator(aggregator), _values(values), _documentHolder(new TiXmlDocument)
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

const sk::util::Pathname&
sk::rt::scope::XmlProcessor::
getLocation() const
{
  return _location;
}

void
sk::rt::scope::XmlProcessor::
start(const sk::util::String& scope)
{
  TiXmlElement* item = findScopeElement(getHandle(), scope);
  if(item != 0) {
    process(item, _scopeBuffer, _aggregator);
  }
}

TiXmlElement*
sk::rt::scope::XmlProcessor::
findScopeElement(const TiXmlHandle& handle, const sk::util::String& name) 
{
  TiXmlElement* default_item = 0;
  for(TiXmlElement* item=handle.FirstChild("scope").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    const sk::util::String scope = sk::util::String(item->Attribute("name")).trim();
    if(name.isEmpty() == true || name.equals(scope) == true) {
      _scopeBuffer = scope;
      return item;
    }
    if(scope.isEmpty() == true && default_item == 0) {
      default_item = item;
    }
  }
  _scopeBuffer = name;
  return default_item;
}

void
sk::rt::scope::XmlProcessor::
process(const TiXmlHandle& handle, const sk::util::String& scopeBuffer, scope::Aggregator& aggregator) 
{
  _scopeBuffer = scopeBuffer;
  _values["scope"] = _scopeBuffer;

  updateConfig(handle, aggregator.getConfigForUpdate());

  for(TiXmlElement* item=handle.FirstChild("scope").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    const sk::util::String name = sk::util::String(item->Attribute("name")).trim();
    if(name.isEmpty() == true) {
      continue;
    }
    process(item, scopeBuffer + '-' + name, aggregator.obtain(name));
  }
}

void
sk::rt::scope::XmlProcessor::
updateConfig(const TiXmlHandle& handle, scope::IConfig& config)
{
  for(TiXmlElement* item=handle.FirstChild("log").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    updateLogInfo(item, config);
  }
  updateProperties(handle, config);
}

bool 
sk::rt::scope::XmlProcessor::
attribute(TiXmlElement* element, const sk::util::String& name, bool fallback) 
{
  if(element) {
    const char* value = element->Attribute(name.getChars());
    if(value) {
      return sk::util::Boolean::parseBoolean(expand(value));
    }
  }
  return fallback;
}

const sk::util::String 
sk::rt::scope::XmlProcessor::
attribute(TiXmlElement* element, const sk::util::String& name, const sk::util::String& fallback) 
{
  if(element) {
    const char* value = element->Attribute(name.getChars());
    if(value) {
      return expand(value);
    }
  }
  return fallback;
}

const sk::util::String 
sk::rt::scope::XmlProcessor::
attribute(TiXmlElement* element, const sk::util::String& name, const char* fallback) 
{
  return attribute(element, name, sk::util::String(fallback));
}

void 
sk::rt::scope::XmlProcessor::
updateLogInfo(const TiXmlHandle& handle, scope::IConfig& config) 
{
  config.setLogObject(attribute(handle.ToElement(), "show-object", config.isLogObject()));
  config.setLogThread(attribute(handle.ToElement(), "show-thread", config.isLogThread()));
  config.setLogTime(attribute(handle.ToElement(), "show-time", config.isLogTime()));
  config.setLogPid(attribute(handle.ToElement(), "show-pid", config.isLogPid()));
  config.setTimeFormat(attribute(handle.ToElement(), "time-format", config.getTimeFormat()));

  const sk::util::String eol = attribute(handle.ToElement(), "eol", "").trim().toLowerCase();
  if(eol.equals("unix") == true || eol.equals("lf") == true) {
    config.setLineTerminator("\n");
  }
  else if(eol.equals("windows") == true || eol.equals("dos") || eol.equals("crlf") == true) {
    config.setLineTerminator("\r\n");
  }
  else if(eol.equals("mac") == true || eol.equals("cr") == true) {
    config.setLineTerminator("\r");
  }
  else if(eol.equals("lfcr") == true) {
    config.setLineTerminator("\n\r");
  }

  const sk::util::String destination = attribute(handle.ToElement(), "destination", "").trim();
  if(destination.equals("std::cout") == true) {
    config.setLogDestination(logger::StreamDestination(std::cout));
  }
  else if(destination.equals("std::clog") == true) {
    config.setLogDestination(logger::StreamDestination(std::clog));
  }
  else if(destination.equals("std::cerr") == true) {
    config.setLogDestination(logger::StreamDestination(std::cerr));
  }
  else if(destination.equals("trash") == true) {
    config.setLogDestination(logger::TrashDestination());
  }
  else if(destination.equals("file") == true) {
    for(TiXmlElement* item=handle.FirstChild(destination).ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
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
updateProperties(const TiXmlHandle& handle, scope::IConfig& config) 
{
  for(TiXmlElement* item=handle.FirstChild("property").ToElement(); item ;item=item->NextSiblingElement(item->Value())) {
    const sk::util::String name = attribute(item, "name", "");
    if(name.isEmpty() == false){
      config.setProperty(name, expand(figure_text(item->Attribute("value"), item)));
    }
  }
}

const sk::util::String 
sk::rt::scope::XmlProcessor::
expand(const sk::util::String& value)
{
  std::stringstream stream;
  std::string::size_type index = 0;

  while(true) {
    std::string::size_type start = value.find("#{", index, 2);
    stream << value.substr(index, start - index);

    if(start == std::string::npos) {
      break;
    }
    std::string::size_type end = value.find('}', start + 2);
    stream << _values[value.substr(start + 2, end - start - 2)];
    if(end == std::string::npos) {
      break;
    }
    index = end + 1;
  }
  return stream.str();
}

void
sk::rt::scope::XmlProcessor::
updateFileDestination(const TiXmlHandle& handle, scope::IConfig& config) 
{
  sk::util::Pathname name(attribute(handle.ToElement(), "name", _scopeBuffer), "log");
  sk::util::Pathname location(attribute(handle.ToElement(), "location", "."));
  sk::util::Pathname pathname = location.join(name);
  if(pathname.isExplicit() == false) {
    pathname = sk::util::Pathname(_location).join(pathname);
  }
  logger::FileDestination file(logger::CyclerFactory::create(pathname, attribute(handle.ToElement(), "policy", "")).get(), _aggregator.getArbitrator());

  file.getCycler().setSize(attribute(handle.ToElement(), "size", "10M"));
  file.getCycler().setChunks(attribute(handle.ToElement(), "chunks", attribute(handle.ToElement(), "backups", "3")));

  if(attribute(handle.ToElement(), "ensure-chunks", false) == true) {
    file.getCycler().ensureChunks();
  }
  if(attribute(handle.ToElement(), "use-pipe", false) == true) {
    config.setLogDestination(logger::PipeDestination(file));
  }
  else {
    config.setLogDestination(file);
  }
  config.getLogDestination().makeReady();
}
