/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_STREAM_
#define _SK_RT_LOGGER_STREAM_

#include <sk/util/Object.h>
#include <sk/rt/logger/ScopeProvider.h>
#include <iostream>

namespace sk {
  namespace rt {
    namespace logger {
      class Stream
        : public virtual sk::util::Object 
      {
        public:
          Stream(const sk::util::String& level, const ScopeProvider& provider);
          Stream(const Stream& other);
          virtual ~Stream();

          const sk::util::String getScopeName() const;
          const sk::util::String getLevel() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          
        private:
          Stream& operator = (const Stream& other);
          const ScopeProvider& _provider;
          const sk::util::String _level;
      };

      template<typename T>
      const sk::rt::logger::Stream& operator<<(const sk::rt::logger::Stream& stream, const T& object) {
        std::cerr << stream.getLevel() << ": " << stream.getScopeName() << ": " << object << std::endl;
        return stream;
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_STREAM_ */
