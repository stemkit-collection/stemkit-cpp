/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_
#define _SK_RT_LOGGER_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/rt/logger/Spot.h>
#include <sk/rt/logger/Controller.h>
#include <sk/rt/logger/Stream.h>
#include <sk/rt/logger/ScopeProvider.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;
    }
    class Logger
      : public virtual sk::rt::logger::ScopeProvider
    {
      public:
        Logger(const sk::util::Object& object);
        Logger(const sk::util::String& name);
        virtual ~Logger();

        const sk::util::String getScopeName() const;
        static logger::Controller& controller();

        const logger::Stream error(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream warning(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream notice(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream info(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream debug(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        const logger::Stream detail(const sk::rt::logger::Spot& spot = sk::rt::logger::Spot::NOTSET) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Logger(const Logger& other);
        Logger& operator = (const Logger& other);

        static logger::Controller _controller;
        const sk::util::Object& _object;

        logger::Config& _config;
        sk::util::String _name;
    };
  }
}

#define SK_LOGSPOT sk::rt::logger::Spot::function(__FUNCTION__, __LINE__)

#endif /* _SK_RT_LOGGER_ */
