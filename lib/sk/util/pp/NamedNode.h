/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_NAMEDNODE_H_
#define _SK_UTIL_PP_NAMEDNODE_H_

#include "AbstractCompositeNode.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class NamedNode
        : public sk::util::pp::AbstractCompositeNode,
          public virtual sk::util::pp::Parser
      {
        public:
          NamedNode();
          NamedNode(const std::vector<char>& data, int start, const sk::util::String& name, sk::util::pp::Node* node);
          virtual ~NamedNode();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;

          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminators) const;
          void pushOpenBraket(std::vector<char>& brakets) const;

          // sk::util::pp::Node implementation.
          void output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream) const;

        private:
          NamedNode(const NamedNode& other);
          NamedNode& operator = (const NamedNode& other);

          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_NAMEDNODE_H_ */
