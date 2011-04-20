/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>
#include <sk/util/processor/Mapping.hxx>
#include <sk/util/processor/Copying.hxx>

#include <sk/util/CompoundException.h>

static const sk::util::String __className("sk::util::CompoundException");

namespace {
  struct ExceptionMessageCollector : sk::util::Processor<const sk::util::Exception> {
    ExceptionMessageCollector(sk::util::Strings& strings) 
      : _strings(strings) {}

    void process(const sk::util::Exception& exception) const {
      _strings << '<' + exception.getMessage() + '>';
    }
    sk::util::Strings& _strings;
  };

  const sk::util::Strings makeComponents(const sk::util::String& label, const sk::util::List<sk::util::Exception>& exceptions) {
    sk::util::Strings strings(label);
    exceptions.forEach(ExceptionMessageCollector(strings));
    return strings;
  }
}

sk::util::CompoundException::
CompoundException(const sk::util::List<sk::util::Exception>& exceptions)
  : sk::util::Exception(makeComponents("Compound", exceptions))
{
}

const sk::util::Class
sk::util::CompoundException::
getClass() const
{
  return sk::util::Class(__className);
}
