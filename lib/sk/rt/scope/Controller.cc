/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/scope/Controller.h>
#include <sk/rt/config/Locator.h>

#include "XmlConfigLoader.h"

sk::rt::scope::Controller::
Controller()
{
}

sk::rt::scope::Controller::
~Controller()
{
    // We have to do it here to ensure that a user supplied class gets
    // destroyed before the whole scoping/logging subsystem is brought
    // down. Otherwise, that class may try to log something while a 
    // correspondig scope is already destroyed.
    _aggregator.resetArbitrator();
}

const sk::util::Class
sk::rt::scope::Controller::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Controller");
}

sk::rt::scope::Aggregator&
sk::rt::scope::Controller::
getAggregator() 
{
  return _aggregator;
}

void
sk::rt::scope::Controller::
loadXmlConfig(const config::Locator& locator) 
{
  locator.invoke(XmlConfigLoader(sk::util::String::EMPTY, _aggregator, std::map<std::string, std::string>()));
}

void
sk::rt::scope::Controller::
loadXmlConfig(const sk::util::String& top, const config::Locator& locator) 
{
  locator.invoke(XmlConfigLoader(top, _aggregator, std::map<std::string, std::string>()));
}

void
sk::rt::scope::Controller::
loadXmlConfig(const config::Locator& locator, const std::map<std::string, std::string>& values) 
{
  locator.invoke(XmlConfigLoader(sk::util::String::EMPTY, _aggregator, values));
}

void
sk::rt::scope::Controller::
loadXmlConfig(const sk::util::String& top, const config::Locator& locator, const std::map<std::string, std::string>& values) 
{
  locator.invoke(XmlConfigLoader(top, _aggregator, values));
}
