/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_LOCKER_H_
#define _SK_RT_LOCKER_H_

#include <sk/util/Object.h>
#include <sk/rt/Lock.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    class Locker 
      : public virtual sk::util::Object
    {
      public:
        Locker(sk::rt::Lock& lock);
        virtual ~Locker();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        sk::util::Holder<sk::rt::Lock>::Sharing _lockHolder;
    };
  }
}

#endif /* _SK_RT_LOCKER_H_ */
