/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_CONTROLLER_
#define _SK_RT_LOGGER_CONTROLLER_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/logger/IController.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Config;

      class Controller
        : public virtual sk::rt::logger::IController
      {
        public:
          Controller();
          virtual ~Controller();

          void setStream(std::ostream& stream);
          Config& findConfig(const sk::util::String& name);
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::rt::logger::IController implementation.
          std::ostream& getStream() const;
          
        private:
          Controller(const Controller& other);
          Controller& operator = (const Controller& other);

          sk::util::Holder<std::ostream> _streamHolder;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_CONTROLLER_ */
