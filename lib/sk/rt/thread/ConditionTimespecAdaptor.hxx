/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_THREAD_CONDITIONTIMESPECADAPTOR_HXX_
#define _SK_RT_THREAD_CONDITIONTIMESPECADAPTOR_HXX_

#include <sk/rt/thread/Condition.h>
#include <sys/time.h>

namespace sk {
  namespace rt {
    namespace thread {
      template<typename T>
      class ConditionTimespecAdaptor : public virtual sk::rt::thread::Condition {
        public:
          ConditionTimespecAdaptor(T& mediator)
            : _mediator(mediator), _channel(0), _calculated(false) {}

        protected:
          // sk::rt::thread::Condition implementation.
          sk::rt::thread::Condition& on(int channel) {
            _channel = channel;
            return *this;
          }

          void wait(uint64_t milliseconds) {
            if(milliseconds == 0) {
              _mediator.wait(_channel);
              return;
            }
            if(_calculated == false) {
              struct timeval now;
              if(::gettimeofday(&now, 0) < 0) {
                throw sk::rt::SystemException("gettimeofday");
              }
              _moment.tv_sec = now.tv_sec + (milliseconds / 1000);
              _moment.tv_nsec = (now.tv_usec + ((milliseconds % 1000) * 1000)) * 1000;

              _calculated = true;
            }
            _mediator.wait(_channel, _moment);
          }

          void announce() {
            _mediator.announce(_channel);
          }

        private:
          T& _mediator;
          int _channel;
          bool _calculated;
          struct timespec _moment;
      };
    }
  }
}


#endif /* _SK_RT_THREAD_CONDITIONTIMESPECADAPTOR_HXX_ */