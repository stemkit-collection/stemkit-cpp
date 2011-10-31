/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/rt/event/PosixSignal.h>
#include <sk/rt/event/PosixSignalVisitor.h>

#include <sk/util/Class.h>
#include <sk/util/UnsupportedOperationException.h>

#include <signal.h>

namespace {
  const sk::util::String __className("sk::rt::event::PosixSignal");
}

#define DEFINE_SIGNAL(signal) const sk::rt::event::PosixSignal sk::rt::event::PosixSignal::signal(SIG##signal, #signal)

DEFINE_SIGNAL(HUP);
DEFINE_SIGNAL(INT);
DEFINE_SIGNAL(QUIT);
DEFINE_SIGNAL(PIPE);
DEFINE_SIGNAL(CHLD);
DEFINE_SIGNAL(TERM);
DEFINE_SIGNAL(ALRM);
DEFINE_SIGNAL(USR1);
DEFINE_SIGNAL(USR2);

sk::rt::event::PosixSignal::
PosixSignal(const int signal, const sk::util::String& name)
  : _signal(signal), _name(name)
{
}

sk::rt::event::PosixSignal::
~PosixSignal()
{
}

const sk::util::Class
sk::rt::event::PosixSignal::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::rt::event::PosixSignal::
toString() const
{
  return "SIG" + _name;
}

const sk::util::String
sk::rt::event::PosixSignal::
inspect() const
{
  return "<" + getClass().getName() + ": " + toString() + "/" + sk::util::String::valueOf(_signal) + ">";
}

void 
sk::rt::event::PosixSignal::
accept(const sk::rt::event::Visitor& visitor) const
{
  const sk::rt::event::PosixSignalVisitor* pointer = dynamic_cast<const sk::rt::event::PosixSignalVisitor*>(&visitor);
  if(pointer == 0) {
    return;
  }
  const sk::rt::event::PosixSignalVisitor& posixSignalVisitor = *pointer;

  switch(_signal) {
    case SIGHUP: {
      posixSignalVisitor.visitSIGHUP(*this);
      break;
    }
    case SIGINT: {
      posixSignalVisitor.visitSIGINT(*this);
      break;
    }
    case SIGQUIT: {
      posixSignalVisitor.visitSIGQUIT(*this);
      break;
    }
    case SIGPIPE: {
      posixSignalVisitor.visitSIGPIPE(*this);
      break;
    }
    case SIGCHLD: {
      posixSignalVisitor.visitSIGCHLD(*this);
      break;
    }
    case SIGTERM: {
      posixSignalVisitor.visitSIGTERM(*this);
      break;
    }
    case SIGALRM: {
      posixSignalVisitor.visitSIGALRM(*this);
      break;
    }
    case SIGUSR1: {
      posixSignalVisitor.visitSIGUSR1(*this);
      break;
    }
    case SIGUSR2: {
      posixSignalVisitor.visitSIGUSR2(*this);
      break;
    }
  }
}
