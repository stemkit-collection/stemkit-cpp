/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_SYS_EVENT_POSIXSIGNALVISITOR_H_
#define _SK_SYS_EVENT_POSIXSIGNALVISITOR_H_

#include <sk/sys/event/Visitor.h>

namespace sk {
  namespace sys {
    namespace event {
      class PosixSignal;

      class PosixSignalVisitor 
        : public virtual sk::sys::event::Visitor
      {
        public:
          virtual void visitSIGHUP(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGINT(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGQUIT(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGPIPE(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGCHLD(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGTERM(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGALRM(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGUSR1(const sk::sys::event::PosixSignal& signal) const = 0;
          virtual void visitSIGUSR2(const sk::sys::event::PosixSignal& signal) const = 0;
      };
    }
  }
}

#endif /* _SK_SYS_EVENT_POSIXSIGNALVISITOR_H_ */
