/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_SYS_EVENT_POSIXSIGNAL_H_
#define _SK_SYS_EVENT_POSIXSIGNAL_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/sys/Event.h>

namespace sk {
  namespace sys {
    namespace event {
      class PosixSignal 
        : public sk::sys::Event
      {
        public:
          virtual ~PosixSignal();

          static const sk::sys::event::PosixSignal HUP;
          static const sk::sys::event::PosixSignal INT;
          static const sk::sys::event::PosixSignal QUIT;
          static const sk::sys::event::PosixSignal PIPE;
          static const sk::sys::event::PosixSignal CHLD;
          static const sk::sys::event::PosixSignal TERM;
          static const sk::sys::event::PosixSignal ALRM;
          static const sk::sys::event::PosixSignal USR1;
          static const sk::sys::event::PosixSignal USR2;
      
          // sk::sys::Event implementation.
          void accept(const sk::sys::event::Visitor& visitor) const;

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

#endif /* _SK_SYS_EVENT_POSIXSIGNAL_H_ */
