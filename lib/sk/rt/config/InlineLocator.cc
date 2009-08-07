/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/config/StreamProcessor.h>

#include <sstream>

sk::rt::config::InlineLocator::
InlineLocator(const sk::util::String& content)
  : _content(content)
{
}

sk::rt::config::InlineLocator::
InlineLocator(const sk::util::String& content, const Locator& other)
  : _content(content), _locatorHolder(other)
{
}

sk::rt::config::InlineLocator::
InlineLocator()
{
}

sk::rt::config::InlineLocator::
~InlineLocator()
{
}

const sk::util::Class
sk::rt::config::InlineLocator::
getClass() const
{
  return sk::util::Class("sk::rt::config::InlineLocator");
}

void
sk::rt::config::InlineLocator::
invoke(const StreamProcessor& processor) const
{
  if(_locatorHolder.isEmpty() == false) {
    _locatorHolder.get().invoke(processor);
  }
  try {
    std::istringstream stream(_content);
    processor.process(stream, ".");
  }
  catch(const sk::util::MissingResourceException& exception) {}
}
