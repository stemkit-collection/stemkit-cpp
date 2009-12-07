/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_
#define _SK_RT_SCOPE_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>

#include <sk/rt/scope/Controller.h>
#include <sk/rt/logger/Stream.h>
#include <sk/rt/logger/IScope.h>
#include <sk/rt/scope/IConfig.h>

namespace sk {
  namespace rt {
    class Scope
      : public virtual logger::IScope,
        public virtual scope::ThreadInfo
    {
      public:
        Scope(const sk::util::Object& object);
        Scope(const sk::util::String& name);
        Scope(const Scope& other);
        virtual ~Scope();

        Scope& operator = (const Scope& other);

        static scope::Controller& controller();
        const Scope scope(const sk::util::String& name) const;

        const logger::Stream error(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream warning(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream stat(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream info(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream notice(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream debug(const sk::util::String& label = sk::util::String::EMPTY) const;
        const logger::Stream detail(const sk::util::String& label = sk::util::String::EMPTY) const;

        const sk::util::String getProperty(const sk::util::String& name) const;
        bool hasProperty(const sk::util::String& name) const;

        const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const;
        const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const;
        int getProperty(const sk::util::String& name, int fallback) const;
        bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        // sk::rt::logger::IScope implementation.
        void aggregateScopeName(std::ostream& stream) const;
        const sk::util::Object& getObject() const;
        const scope::IConfig& getConfig() const;
        sk::rt::Lock& getLock() const;

        // sk::rt::scope::ThreadInfo implementation.
        uint64_t currentThreadId() const;
        
      private:
        Scope(const Scope& parent, const sk::util::String& name);

        scope::Aggregator& getAggregator() const;

        sk::util::String _name;
        const Scope& _parent;
        const sk::util::Object& _object;
        scope::Aggregator& _aggregator;

        static scope::Controller* _controller;
    };
  }
}

#endif /* _SK_RT_SCOPE_ */
