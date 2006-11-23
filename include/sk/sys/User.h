/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_USER_
#define _SK_SYS_USER_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace sys {
    class User
      : public virtual sk::util::Object 
    {
      public:
        // Default copy constructor is sufficient for now.
        // User(const User& other);
        virtual ~User();

        const sk::util::String getName() const;
        int getUid() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        static const sk::sys::User find(const sk::util::String& name);

      private:
        User(const sk::util::String& name, int id);
        User& operator = (const User& other);

        sk::util::String _name;
        int _id;
    };
  }
}

#endif /* _SK_SYS_USER_ */
