/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_ABSTRACTCOMPOSITENODE_H_
#define _SK_UTIL_PP_ABSTRACTCOMPOSITENODE_H_

#include <sk/util/ArrayList.hxx>
#include "Node.h"
#include <vector>

namespace sk {
  namespace util {
    namespace pp {
      class AbstractCompositeNode
        : public virtual sk::util::pp::Node
      {
        public:
          AbstractCompositeNode();
          AbstractCompositeNode(const std::vector<char>& data, int start);
          virtual ~AbstractCompositeNode();

          void setLength(int length);
          int addNode(sk::util::pp::Node* node);

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;

          // sk::util::pp::Node implementation.
          int startPosition() const;
          int endPosition() const;
          void output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream) const;
          bool isGonnaBreak() const;

        protected:
          const sk::util::pp::Node& getNode(int index) const;
          int getNodeCount() const;
          void forEachNode(const sk::util::Processor<const sk::util::pp::Node>& processor) const;
          bool hasBreakingNode() const;
          void output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream, bool breaking) const;

        private:
          AbstractCompositeNode(const AbstractCompositeNode& other);
          AbstractCompositeNode& operator = (const AbstractCompositeNode& other);

          sk::util::ArrayList<sk::util::pp::Node> _nodes;
          int _start;
          int _end;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_ABSTRACTCOMPOSITENODE_H_ */
