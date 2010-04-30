/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _TEST_HANDLER_H_
#define _TEST_HANDLER_H_

#include <sk/util/Object.h>
#include <sk/rt/Scope.h>

namespace test {
  class Handler 
    : public virtual sk::util::Object
  {
    public:
      Handler(int argc, const char* const argv[]);
      virtual ~Handler();

      void start();
  
      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;
  
    private:
      Handler(const Handler& other);
      Handler& operator = (const Handler& other);

      sk::rt::Scope _scope;
  };
}

#endif /* _TEST_HANDLER_H_ */
