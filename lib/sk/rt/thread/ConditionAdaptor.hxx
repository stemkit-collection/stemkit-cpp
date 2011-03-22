/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_THREAD_CONDITIONADAPTOR_HXX_
#define _SK_RT_THREAD_CONDITIONADAPTOR_HXX_

#include <sk/rt/thread/Condition.h>

namespace sk {
  namespace rt {
    namespace thread {
      template<typename T>
      class ConditionAdaptor : public virtual sk::rt::thread::Condition {
        public:
          ConditionAdaptor(T& mediator)
            : _mediator(mediator), _channel(0) {}

        protected:
          // sk::rt::thread::Condition implementation.
          sk::rt::thread::Condition& on(int channel) {
            _channel = channel;
            return *this;
          }

          void wait(uint64_t milliseconds) {
            _mediator.wait(_channel, milliseconds);
          }

          void announce() {
            _mediator.announce(_channel);
          }

        private:
          T& _mediator;
          int _channel;
      };
    }
  }
}


#endif /* _SK_RT_THREAD_CONDITIONADAPTOR_HXX_ */
