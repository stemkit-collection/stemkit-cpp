/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_POSIXSIGNAL_H_
#define _SK_RT_EVENT_POSIXSIGNAL_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/rt/Event.h>

namespace sk {
  namespace rt {
    namespace event {
      class PosixSignal 
        : public sk::rt::Event
      {
        public:
          virtual ~PosixSignal();

          static const sk::rt::event::PosixSignal HUP;
          static const sk::rt::event::PosixSignal INT;
          static const sk::rt::event::PosixSignal QUIT;
          static const sk::rt::event::PosixSignal PIPE;
          static const sk::rt::event::PosixSignal CHLD;
          static const sk::rt::event::PosixSignal TERM;
          static const sk::rt::event::PosixSignal ALRM;
          static const sk::rt::event::PosixSignal USR1;
          static const sk::rt::event::PosixSignal USR2;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String toString() const;
          const sk::util::String inspect() const;
      
        private:
          PosixSignal(const int signal, const sk::util::String& name);
          PosixSignal(const PosixSignal& other);
          PosixSignal& operator = (const PosixSignal& other);

          const int _signal;
          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_RT_EVENT_POSIXSIGNAL_H_ */
