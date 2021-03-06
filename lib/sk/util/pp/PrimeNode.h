/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_PRIMENODE_H_
#define _SK_UTIL_PP_PRIMENODE_H_

#include <sk/util/ArrayList.hxx>

#include "Node.h"
#include "Parser.h"

namespace sk {
  namespace util {
    namespace pp {
      class PrimeNode
        : public virtual sk::util::pp::Node,
          public virtual sk::util::pp::Parser
      {
        public:
          PrimeNode();
          virtual ~PrimeNode();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::util::pp::Parser implementation.
          Node* parse(const std::vector<char>& data, int offset, const std::vector<char>& terminator) const;
          void pushOpenBraket(std::vector<char>& brakets) const;

          // sk::util::pp::Node implementation.
          int startPosition() const;
          int endPosition() const;
          void output(const Configurator& configurator, const sk::util::String& indent, std::ostream& stream) const;
          bool isGonnaBreak() const;

        private:
          PrimeNode(const PrimeNode& other);
          PrimeNode& operator = (const PrimeNode& other);

          sk::util::ArrayList<Parser> _parsers;
      };
    }
  }
}

#endif /* _SK_UTIL_PP_PRIMENODE_H_ */
