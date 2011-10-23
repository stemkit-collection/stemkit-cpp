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

      bool isError() const {
        return _scope.error().isEnabled();
      }
      
      bool isStat() const {
        return _scope.stat().isEnabled();
      }
      
      bool isWarning() const {
        return _scope.warning().isEnabled();
      }

      bool isInfo() const {
        return _scope.info().isEnabled();
      }

      bool isNotice() const {
        return _scope.notice().isEnabled();
      }

      bool isDetail() const {
        return _scope.detail().isEnabled();
      }

      bool isDebug() const {
        return _scope.debug().isEnabled();
      }

      bool logError(const sk::util::String& message) const {
        return (_scope.error() << message).isEnabled();
      }
      
      bool logStat(const sk::util::String& message) const {
        return (_scope.stat() << message).isEnabled();
      }
      
      bool logWarning(const sk::util::String& message) const {
        return (_scope.warning() << message).isEnabled();
      }

      bool logInfo(const sk::util::String& message) const {
        return (_scope.info() << message).isEnabled();
      }

      bool logNotice(const sk::util::String& message) const {
        return (_scope.notice() << message).isEnabled();
      }

      bool logDetail(const sk::util::String& message) const {
        return (_scope.detail() << message).isEnabled();
      }

      bool logDebug(const sk::util::String& message) const {
        return (_scope.debug() << message).isEnabled();
      }

    private:
      const sk::rt::Scope& _scope;
  };
}

#endif /* _RUBY_LOGGERADAPTOR_ */
