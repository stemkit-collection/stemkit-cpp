%include "stl.i"
%include "typemaps.i"
%include "exception.i"

%module "SK::rt"

%{
#include <sk/rt/config/UprootLocator.h>
#include <sk/rt/config/CwdUprootLocator.h>
#include <sk/rt/config/HomeLocator.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/scope/Controller.h>
#include <sk/rt/Scope.h>

using sk::rt::config::StreamProcessor;
using sk::rt::config::NamedStreamOpener;

#include "LoggerAdaptor.h"
#include <sk/util/SystemExit.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>

%}

namespace sk
{
  namespace util {
    %naturalvar String;
    class String;
  }
}

%typemaps_std_string(sk::util::String, char, SWIG_AsCharPtrAndSize, SWIG_FromCharPtrAndSize, %checkcode(STDSTRING));
%template("StringHash") std::map<std::string, std::string>;

%exception {
  try {
    $action
  }
  catch(const sk::util::SystemExit& exception) {
    std::cerr << exception.getMessage() << std::endl;
    exit(exception.getCode());
  }
  catch(const std::exception& exception) {
    SWIG_exception(SWIG_RuntimeError, exception.what());
    throw;
  }
}

%ignore getClass;
%ignore *::SpotLocator::openStream;

%include <sk/rt/config/Locator.h>
%include <sk/rt/config/SpotLocator.h>
%include <sk/rt/config/UprootLocator.h>
%include <sk/rt/config/CwdUprootLocator.h>
%include <sk/rt/config/HomeLocator.h>
%include <sk/rt/config/InlineLocator.h>

%ignore *::Controller::getAggregator;
%rename(load_xml_config) *::Controller::loadXmlConfig;

%include <sk/rt/scope/Controller.h>

%ignore *::Scope::error;
%ignore *::Scope::stat;
%ignore *::Scope::warning;
%ignore *::Scope::notice;
%ignore *::Scope::info;
%ignore *::Scope::debug;
%ignore *::Scope::detail;

%rename(property) *::Scope::getProperty;
%rename(has_property) *::Scope::hasProperty;
%predicate hasProperty;
%ignore *::LoggerAdaptor::LoggerAdaptor;

%include <sk/rt/Scope.h>
%include "LoggerAdaptor.h"

%extend sk::rt::Scope {
  const ruby::LoggerAdaptor logger() const {
    return ruby::LoggerAdaptor(*$self);
  }
}

%extend sk::rt::config::SpotLocator {
  SpotLocator(const sk::util::String& item, const sk::util::String& location) {
    return new sk::rt::config::SpotLocator(item, location);
  }
}

%extend sk::rt::config::UprootLocator {
  UprootLocator(const sk::util::String& item, const sk::util::String& location) {
    return new sk::rt::config::UprootLocator(item, location);
  }
}

%extend sk::rt::scope::Controller {
  void loadXmlConfig(const sk::util::String& top, const config::Locator& locator) {
    self->loadXmlConfig(sk::util::StringArray(top), locator);
  }

  void loadXmlConfig(const sk::util::String& top, const config::Locator& locator, const std::map<std::string, std::string>& values) {
    self->loadXmlConfig(sk::util::StringArray(top), locator, values);
  }
}
