/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_THREAD_CONDITIONTIMINGADAPTOR_HXX_
#define _SK_RT_THREAD_CONDITIONTIMINGADAPTOR_HXX_

#include <sk/rt/thread/Condition.h>
#include <sk/rt/Time.h>

namespace sk {
  namespace rt {
    namespace thread {
      template<typename T>
      class ConditionTimingAdaptor : public virtual sk::rt::thread::Condition {
        public:
          ConditionTimingAdaptor(T& mediator)
            : _time(sk::rt::Time::at(0)), _mediator(mediator), _channel(0) {}

          bool isMomentReached() const {
            if(_time.getSeconds() == 0) {
              return false;
            }
            return sk::rt::Time::now() < _time ? false : true;
          }

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
            if(_time.getSeconds() == 0) {
              _time = sk::rt::Time::now().offsetMilliseconds(milliseconds);
              _time.fill(_moment);
            }
            _mediator.wait(_channel, _moment);
          }

          void announce() {
            _mediator.announce(_channel);
          }

        private:
          T& _mediator;
          int _channel;
          sk::rt::Time _time;
          struct timespec _moment;
      };
    }
  }
}


#endif /* _SK_RT_THREAD_CONDITIONTIMINGADAPTOR_HXX_ */
