/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_TIME_H_
#define _SK_RT_TIME_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace rt {
    class Time 
      : public virtual sk::util::Object
    {
      public:
        virtual ~Time();

        static const sk::rt::Time now();
        const sk::util::String format(const sk::util::String& specification) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Time();
        Time& operator = (const Time& other);

        const struct tm& figure_localtime(struct tm& tm_buffer) const;

        time_t _time;
    };
  }
}

#endif /* _SK_RT_TIME_H_ */
