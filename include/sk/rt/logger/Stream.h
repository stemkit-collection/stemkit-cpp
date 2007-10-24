/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_STREAM_
#define _SK_RT_LOGGER_STREAM_

#include <sk/util/Object.h>
#include <sk/rt/logger/IScope.h>
#include <sk/rt/logger/Level.h>
#include <ostream>

namespace sk {
  namespace rt {
    namespace logger {
      class Level;

      class Stream
        : public virtual sk::util::Object 
      {
        public:
          Stream(const Level& level, const logger::IScope& scope);
          Stream(const Stream& other);
          virtual ~Stream();

          bool isEnabled() const;
          std::ostream& getStream() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Stream& operator = (const Stream& other);

          const logger::IConfig& _config;
          std::ostream& _stream;
          bool _enabled;
      };

      template<typename T>
      inline const sk::rt::logger::Stream& operator<<(const sk::rt::logger::Stream& stream, const T& object) {
        if(stream.isEnabled() == true) {
          stream.getStream() << object;
        }
        return stream;
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_STREAM_ */
