/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_STOPWATCH_H_
#define _SK_RT_STOPWATCH_H_

#include <sk/util/Object.h>
#include <sys/time.h>

namespace sk {
  namespace rt {
    class StopWatch 
      : public virtual sk::util::Object
    {
      public:
        StopWatch();
        virtual ~StopWatch();

        void start();
        void stop();
        bool isTicking() const;
        uint64_t getMicroseconds() const;
        uint64_t getMilliseconds() const;

        static const sk::util::String toString(uint64_t microseconds);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
        const sk::util::String inspect() const;
    
      private:
        StopWatch(const StopWatch& other);
        StopWatch& operator = (const StopWatch& other);

        struct timeval _start;
        struct timeval _stop;
        bool _started;
        bool _stopped;
    };
  }
}

#endif /* _SK_RT_STOPWATCH_H_ */
