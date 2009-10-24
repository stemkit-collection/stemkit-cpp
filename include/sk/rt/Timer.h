/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_TIMER_H_
#define _SK_RT_TIMER_H_

#include <sk/util/Object.h>
#include <sys/time.h>

namespace sk {
  namespace rt {
    class Timer 
      : public virtual sk::util::Object
    {
      public:
        Timer();
        virtual ~Timer();

        void start();
        void stop();
        bool isTicking() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Timer(const Timer& other);
        Timer& operator = (const Timer& other);

        struct timeval _start;
        struct timeval _stop;
        bool _started;
        bool _stopped;
    };
  }
}

#endif /* _SK_RT_TIMER_H_ */
