/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_USER_
#define _SK_SYS_USER_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class User
      : public virtual sk::util::Object 
    {
      public:
        User();
        virtual ~User();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        User(const User& other);
        User& operator = (const User& other);
    };
  }
}

#endif /* _SK_SYS_USER_ */
