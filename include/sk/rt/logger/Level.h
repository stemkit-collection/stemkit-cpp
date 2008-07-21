/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_LEVEL_
#define _SK_RT_LOGGER_LEVEL_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace rt {
    namespace logger {
      class Level
        : public virtual sk::util::Object 
      {
        public:
          virtual ~Level();

          static const Level& valueOf(const sk::util::String& name);
          int toInt() const;
          const sk::util::String& getName() const;
          
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String toString() const;

          bool operator==(const Level& other) const;

          static const Level SK_L_NONE;
          static const Level SK_L_ERROR;
          static const Level SK_L_STAT;
          static const Level SK_L_WARNING;
          static const Level SK_L_INFO;
          static const Level SK_L_NOTICE;
          static const Level SK_L_DETAIL;
          static const Level SK_L_DEBUG;
          
        private:
          Level(const sk::util::String& name);
          Level(const Level& other);
          Level& operator = (const Level& other);

          static std::vector<Level*> _levels;

          int _value;
          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_RT_LOGGER_LEVEL_ */
