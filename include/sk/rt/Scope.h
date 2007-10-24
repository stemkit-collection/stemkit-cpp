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

#include <sk/rt/logger/Spot.h>
#include <sk/rt/scope/Controller.h>
#include <sk/rt/logger/Stream.h>
#include <sk/rt/scope/IScope.h>
#include <sk/rt/scope/IConfig.h>

namespace sk {
  namespace rt {
    class Scope
      : public virtual scope::IScope
    {
      public:
        Scope(const sk::util::Object& object);
        Scope(const sk::util::String& name);
        Scope(const Scope& other);
        virtual ~Scope();

        static scope::Controller& controller();
        const Scope scope(const sk::util::String& name) const;

        const logger::Stream error(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream warning(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream notice(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream info(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream debug(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream detail(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;

        const sk::util::String getProperty(const sk::util::String& name) const;
        bool hasProperty(const sk::util::String& name) const;

        const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const;
        const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const;
        int getProperty(const sk::util::String& name, int fallback) const;
        bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::rt::scope::IScope implementation.
        void agregateScopeName(std::ostream& stream) const;
        const sk::util::Object& getObject() const;
        const scope::IConfig& getConfig() const;
        
      private:
        Scope(const Scope& parent, const sk::util::String& name);
        Scope& operator = (const Scope& other);

        static scope::Controller _controller;
        const sk::util::Object& _object;

        const Scope& _parent;
        const scope::IConfig& _config;
        sk::util::String _name;
    };
  }
}

#define SK_LOGSPOT sk::rt::logger::Spot::function(__FUNCTION__, __LINE__)

#endif /* _SK_RT_SCOPE_ */
