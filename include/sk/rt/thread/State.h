/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_STATE_H_
#define _SK_RT_THREAD_STATE_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

namespace sk {
  namespace rt {
    namespace thread {
      class State
        : public virtual sk::util::Object
      {
        public:
          virtual ~State();
          static const State& valueOf(const sk::util::String& name);
          int toInt() const;
          const sk::util::String& getName() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String toString() const;

          bool operator==(const State& other) const;

          static const State SK_T_NEW;
          static const State SK_T_STARTED;
          static const State SK_T_RUNNING;
          static const State SK_T_EXITED;
          static const State SK_T_STOPPED;
          static const State SK_T_EXCEPTION;

        private:
          State(const sk::util::String& name);
          State(const State& other);
          State& operator = (const State& other);

          static std::vector<State*> _states;

          int _value;
          const sk::util::String _name;
      };

      std::ostream& operator<<(std::ostream& stream, const State& state);
    }
  }
}

#endif /* _SK_RT_THREAD_STATE_H_ */
