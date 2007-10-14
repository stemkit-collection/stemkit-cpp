/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_LEVEL_
#define _SK_RT_LOGGER_LEVEL_

#include <sk/util/Object.h>

namespace sk {
  namespace rt {
    namespace logger {
      class Level
        : public virtual sk::util::Object 
      {
        public:
          virtual ~Level();

          int toInt() const;
          const sk::util::String& getName() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          bool operator==(const Level& other) const;

          static const Level ERROR;
          static const Level WARNING;
          static const Level INFO;
          static const Level DEBUG;
          static const Level NOTICE;
          static const Level DETAIL;
          
        private:
          Level(const sk::util::String& name);
          Level(const Level& other);
          Level& operator = (const Level& other);

          static int _counter;

          int _value;
          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_LEVEL_ */
