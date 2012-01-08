/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_CONFIG_INLINELOCATOR_H_
#define _SK_RT_CONFIG_INLINELOCATOR_H_

#include <sk/rt/config/Locator.h>
#include <sk/rt/config/NamedStreamOpener.h>

#include <sk/util/String.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace config {
      class InlineLocator
        : public virtual Locator
      {
        public:
          InlineLocator(const sk::util::String& content);
          InlineLocator(const sk::util::String& content, const Locator& other);
          // Default copy constructor is OK here.
          // InlineLocator(const InlineLocator& other);
          virtual ~InlineLocator();

          // sk::rt::config::Locator implementation.
          void invoke(const StreamProcessor& processor) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          InlineLocator();
          InlineLocator& operator = (const InlineLocator& other);

          const sk::util::String _content;
          sk::util::Holder<Locator>::Aliasing _locatorHolder;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_INLINELOCATOR_H_ */
