/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_ENVIRONMENT_H_
#define _SK_RT_ENVIRONMENT_H_

#include <sk/util/Properties.h>
#include <vector>

namespace sk {
  namespace rt {
    class Environment
      : public sk::util::Properties
    {
      public:
        Environment();
        Environment(const sk::util::PropertyRegistry& registry);
        virtual ~Environment();

        const std::vector<char*> serialize(std::vector<char>& block) const;
        void install();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Environment(const Environment& other);
        Environment& operator = (const Environment& other);
    };
  }
}

#endif /* _SK_RT_ENVIRONMENT_H_ */
