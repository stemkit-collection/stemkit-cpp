/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_SPOTLOCATOR_
#define _SK_RT_CONFIG_SPOTLOCATOR_

#include <sk/rt/config/Locator.h>
#include <sk/rt/config/NamedStreamOpener.h>

#include <sk/util/String.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace config {
      class SpotLocator
        : public virtual Locator,
          public virtual NamedStreamOpener
      {
        public:
          SpotLocator(const sk::util::String& item, const sk::util::Pathname& location, const SpotLocator& other);
          SpotLocator(const sk::util::String& item, const sk::util::Pathname& location);
          SpotLocator(const sk::util::Pathname& location, const SpotLocator& other);
          SpotLocator(const SpotLocator& other);
          virtual ~SpotLocator();

          static void setStreamOpener(const NamedStreamOpener& opener);
          static void clearStreamOpener();

          // sk::rt::config::Locator implementation.
          void invoke(const StreamProcessor& processor) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        protected:
          static const SpotLocator DUMMY;
          
        private:
          SpotLocator();
          SpotLocator& operator = (const SpotLocator& other);

          // sk::rt::config::NamedStreamOpener imlementation.
          std::istream* openStream(const sk::util::Pathname& pathname) const;
          
          void becomeDummy();
          bool isDummy() const;
          const NamedStreamOpener& getStreamOpener() const;

          const sk::util::String _item;
          const sk::util::Pathname _location;
          sk::util::Holder<SpotLocator> _locatorHolder;

          static sk::util::Holder<const NamedStreamOpener> _streamOpenerHolder;
      };
    }
  }
}

#endif /* _SK_RT_CONFIG_SPOTLOCATOR_ */
