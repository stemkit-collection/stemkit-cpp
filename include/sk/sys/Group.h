/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_GROUP_
#define _SK_SYS_GROUP_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class Group
      : public virtual sk::util::Object 
    {
      public:
        Group();
        virtual ~Group();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        Group(const Group& other);
        Group& operator = (const Group& other);
    };
  }
}

#endif /* _SK_SYS_GROUP_ */
