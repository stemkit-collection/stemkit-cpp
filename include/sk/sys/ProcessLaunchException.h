/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_PROCESSLAUNCHEXCEPTION_H_
#define _SK_SYS_PROCESSLAUNCHEXCEPTION_H_

#include <sk/util/Exception.h>
#include <sk/util/String.h>
#include <sk/util/Strings.h>

namespace sk {
  namespace sys {
    class ProcessLaunchException 
      : public sk::util::Exception
    {
      public:
        ProcessLaunchException(const sk::util::String& message, const sk::util::Strings& cmdline);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        ProcessLaunchException& operator = (const ProcessLaunchException& other);
    };
  }
}

#endif /* _SK_SYS_PROCESSLAUNCHEXCEPTION_H_ */
