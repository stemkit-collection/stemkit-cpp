/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_GROUP_
#define _SK_SYS_GROUP_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace sys {
    class Group
      : public virtual sk::util::Object 
    {
      public:
        // Default copy constructor is sufficient for now.
        // Group(const Group& other);
        virtual ~Group();

        const sk::util::String getName() const;
        int getGid() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        static const sk::sys::Group find(const sk::util::String& name);
        
      private:
        Group(const sk::util::String& name, int id);
        Group& operator = (const Group& other);

        sk::util::String _name;
        int _id;
    };
  }
}

#endif /* _SK_SYS_GROUP_ */
