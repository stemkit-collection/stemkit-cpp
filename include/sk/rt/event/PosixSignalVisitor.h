/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_RT_EVENT_POSIXSIGNALVISITOR_H_
#define _SK_RT_EVENT_POSIXSIGNALVISITOR_H_

#include <sk/rt/event/Visitor.h>

namespace sk {
  namespace rt {
    namespace event {
      class PosixSignalVisitor 
        : public virtual sk::rt::event::Visitor
      {
        public:
          virtual void visitSIGHUP(const sk::rt::Event& event) const = 0;
          virtual void visitSIGINT(const sk::rt::Event& event) const = 0;
          virtual void visitSIGQUIT(const sk::rt::Event& event) const = 0;
          virtual void visitSIGPIPE(const sk::rt::Event& event) const = 0;
          virtual void visitSIGCHLD(const sk::rt::Event& event) const = 0;
          virtual void visitSIGTERM(const sk::rt::Event& event) const = 0;
          virtual void visitSIGALRM(const sk::rt::Event& event) const = 0;
          virtual void visitSIGUSR1(const sk::rt::Event& event) const = 0;
          virtual void visitSIGUSR2(const sk::rt::Event& event) const = 0;
      };
    }
  }
}

#endif /* _SK_RT_EVENT_POSIXSIGNALVISITOR_H_ */
