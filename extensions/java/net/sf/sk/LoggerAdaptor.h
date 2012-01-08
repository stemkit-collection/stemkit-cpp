/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _RUBY_LOGGERADAPTOR_
#define _RUBY_LOGGERADAPTOR_

#include <sk/util/String.h>
#include <sk/rt/Scope.h>

namespace ruby {
  class LoggerAdaptor
  {
    public:
      LoggerAdaptor(const sk::rt::Scope& scope)
        : _scope(scope) {}

      bool error(const sk::util::String& message) const {
        return (_scope.error() << message).isEnabled();
      }

      bool stat(const sk::util::String& message) const {
        return (_scope.stat() << message).isEnabled();
      }

      bool warning(const sk::util::String& message) const {
        return (_scope.warning() << message).isEnabled();
      }

      bool notice(const sk::util::String& message) const {
        return (_scope.notice() << message).isEnabled();
      }

      bool info(const sk::util::String& message) const {
        return (_scope.info() << message).isEnabled();
      }

      bool debug(const sk::util::String& message) const {
        return (_scope.debug() << message).isEnabled();
      }

      bool detail(const sk::util::String& message) const {
        return (_scope.detail() << message).isEnabled();
      }

    private:
      const sk::rt::Scope& _scope;
  };
}

#endif /* _RUBY_LOGGERADAPTOR_ */
