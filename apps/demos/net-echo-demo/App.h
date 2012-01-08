/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _ECHO_APP_H_
#define _ECHO_APP_H_

#include <sk/util/Object.h>
#include <sk/util/Pathname.h>
#include <sk/rt/Scope.h>
#include <sk/net/InetSocketAddress.h>

namespace echo {
  class App
    : public virtual sk::util::Object
  {
    public:
      App(const sk::util::String& name, const int argc, const char* const argv[]);
      virtual ~App();

      const sk::net::InetSocketAddress& endpoint() const;
      const sk::util::Pathname& program() const;
      const sk::rt::Scope& scope() const;

      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;

    private:
      App(const App& other);
      App& operator = (const App& other);

      const sk::rt::Scope _scope;
      const sk::util::Pathname _program;
      const sk::net::InetSocketAddress _endpoint;
  };
}

#endif /* _ECHO_APP_H_ */
