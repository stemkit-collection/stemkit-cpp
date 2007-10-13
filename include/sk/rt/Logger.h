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

namespace sk {
  namespace rt {
    class Logger
      : public virtual sk::util::Object 
    {
      public:
        Logger(const sk::util::Object& object);
        Logger(const sk::util::String& name);
        virtual ~Logger();

        static logger::Controller& controller();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Logger(const Logger& other);
        Logger& operator = (const Logger& other);

        static logger::Controller _controller;
    };
  }
}

#define SK_LOGSPOT sk::rt::logger::Spot::function(__FUNCTION__, __LINE__)

#endif /* _SK_RT_LOGGER_ */
