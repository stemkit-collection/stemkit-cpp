/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_COLLECTIONNODE_H_
#define _SK_UTIL_PP_COLLECTIONNODE_H_

#include "AbstractCompositeNode.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class CollectionNode
        : public sk::util::pp::AbstractCompositeNode,
          public virtual sk::util::pp::Parser
      {
        public:
          CollectionNode();
          CollectionNode(const std::vector<char>& data, int start);
          virtual ~CollectionNode();

          void setPrefix(const sk::util::String& prefix);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;

          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const;
          void pushOpenBraket(std::vector<char>& brakets) const;

          // sk::util::pp::Node implementation.
          void output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream) const;

        private:
          CollectionNode(const CollectionNode& other);
          CollectionNode& operator = (const CollectionNode& other);

          sk::util::String _prefix;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_COLLECTIONNODE_H_ */
