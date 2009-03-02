/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_LOCKER_HXX_
#define _SK_RT_LOCKER_HXX_

#include <sk/util/Holder.hxx>
#include <sk/rt/Lock.h>

namespace sk {
  namespace rt {
    template<typename L>
    class Locker 
    {
      public:
        Locker(L& lock);
        ~Locker();
    
      private:
        sk::util::Holder<L, sk::util::slot::policy::Sharing<L> > _lockHolder;
    };
  }
}

#endif /* _SK_RT_LOCKER_HXX_ */
