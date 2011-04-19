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

sk::util::CompoundException::
CompoundException(const sk::util::List<sk::util::Exception>& exceptions)
  : sk::util::Exception(makeClassNames("Compound", exceptions))
{
}

const sk::util::Class
sk::util::CompoundException::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct ClassNameMapper : sk::util::Mapper<const sk::util::Exception, const sk::util::String> {
    const sk::util::String map(const sk::util::Exception& exception) const {
      return exception.getClass().getName();
    }
  };
}

const sk::util::Strings 
sk::util::CompoundException::
makeClassNames(const sk::util::String& label, const sk::util::List<sk::util::Exception>& exceptions)
{
  sk::util::Strings strings(label);
  exceptions.forEach(sk::util::processor::Mapping<const sk::util::Exception, const sk::util::String>(sk::util::processor::Copying<sk::util::String>(strings), ClassNameMapper()));

  return strings;
}
