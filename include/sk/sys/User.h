/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_USER_
#define _SK_SYS_USER_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/util/Processor.h>
#include <sk/util/String.h>
#include <sk/rt/Logger.h>

struct passwd;

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
        const sk::util::String getComment() const;
        const sk::util::String getHome() const;
        const sk::util::String getShell() const;
        int getUid() const;
        int getGid() const;
        bool authenticate(const sk::util::String& password) const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
        static const User find(const sk::util::String& name);
        static bool find(const sk::util::String& name, sk::util::Holder<sk::sys::User>& holder);
        static void forEach(const sk::util::Processor<const sk::sys::User>& processor);

      private:
        User(const struct passwd& entry);
        User& operator = (const User& other);

        const sk::rt::Logger _logger;
        sk::util::String _name;
        sk::util::String _home;
        sk::util::String _shell;
        sk::util::String _comment;
        int _uid;
        int _gid;
    };
  }
}

#endif /* _SK_SYS_USER_ */
