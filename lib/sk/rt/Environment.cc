/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IllegalArgumentException.h>

#include <sk/rt/Environment.h>
#include <unistd.h>

static const char* __className("sk::rt::Environment");

sk::rt::Environment::
Environment()
{
  for(char** iterator = environ; *iterator ;++iterator) {
    try {
      parseProperty(*iterator);
    }
    catch(const sk::util::IllegalArgumentException& exception) {}
  }
}

sk::rt::Environment::
Environment(const sk::util::PropertyRegistry& registry)
{
}

sk::rt::Environment::
~Environment()
{
}

const sk::util::Class
sk::rt::Environment::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct Serializer : public virtual sk::util::BinaryProcessor<const sk::util::String, const sk::util::String> {
    Serializer(const sk::util::PropertyRegistry& registry, std::vector<char> block, std::vector<char*> references)
      : _registry(registry), _block(block), _references(references) {}

    void process(const sk::util::String& key, const sk::util::String& value) const {
      const sk::util::String data = _registry.dumpProperty(key);
      int index = _block.size();

      _block.insert(_block.end(), data.begin(), data.end());
      _block.push_back(0);

      _references.push_back(&_block[index]);
    }

    const sk::util::PropertyRegistry& _registry;
    std::vector<char>& _block;
    std::vector<char*>& _references;
  };
}

const std::vector<char*>
sk::rt::Environment::
serialize(std::vector<char> block) const
{
  std::vector<char*> references;
  forEach(Serializer(*this, block, references));

  block.push_back(0);
  references.push_back(0);

  return references;
}
