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
#include <algorithm>

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
  : sk::util::Properties(registry)
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
    Serializer(const sk::util::PropertyRegistry& registry, std::vector<char>& block, std::vector<int>& indices)
      : _registry(registry), _block(block), _indices(indices) {}

    void process(const sk::util::String& key, const sk::util::String& value) const {
      _indices.push_back(_block.size());

      const sk::util::String data = _registry.dumpProperty(key);
      _block.insert(_block.end(), data.begin(), data.end());
      _block.push_back(0);
    }

    const sk::util::PropertyRegistry& _registry;
    std::vector<char>& _block;
    std::vector<int>& _indices;
  };

  struct ReferenceMaker {
    ReferenceMaker(std::vector<char*>& references, std::vector<char>& block)
      : _references(references), _block(block) {}

    void operator()(int index) const {
      _references.push_back(&_block[index]);
    }

    std::vector<char*>& _references;
    std::vector<char>& _block;
  };
}

const std::vector<char*>
sk::rt::Environment::
serialize(std::vector<char>& block) const
{
  std::vector<int> indices;
  forEach(Serializer(*this, block, indices));
  block.push_back(0);

  std::vector<char*> references;
  std::for_each(indices.begin(), indices.end(), ReferenceMaker(references, block));
  references.push_back(0);

  return references;
}
