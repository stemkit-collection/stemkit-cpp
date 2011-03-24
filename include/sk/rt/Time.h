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

struct timeval;
struct tm;

namespace sk {
  namespace rt {
    class Time 
      : public virtual sk::util::Object
    {
      public:
        virtual ~Time();

        static const sk::rt::Time now();
        static const sk::rt::Time at(time_t seconds);
        static const sk::rt::Time at(time_t seconds, uint32_t microseconds);

        const sk::util::String format(const sk::util::String& specification) const;
        time_t getSeconds() const;
        uint32_t getMicroseconds() const;
        void fill(struct timespec& moment) const;

        const sk::rt::Time offsetMilliseconds(uint64_t milliseconds) const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
        const sk::util::String toString() const;
    
        static void obtainCurrentTime(struct timeval& timeinfo);

      private:
        Time(time_t seconds, uint32_t microseconds);

        const struct tm& makeLocaltime(struct tm& tm_buffer) const;

        time_t _seconds;
        uint32_t _microseconds;
    };

    bool operator<(const sk::rt::Time& first, const sk::rt::Time& second);
    bool operator>(const sk::rt::Time& first, const sk::rt::Time& second);
    bool operator==(const sk::rt::Time& first, const sk::rt::Time& second);
    bool operator!=(const sk::rt::Time& first, const sk::rt::Time& second);
    bool operator<=(const sk::rt::Time& first, const sk::rt::Time& second);
    bool operator>=(const sk::rt::Time& first, const sk::rt::Time& second);
  }
}

#endif /* _SK_RT_TIME_H_ */
