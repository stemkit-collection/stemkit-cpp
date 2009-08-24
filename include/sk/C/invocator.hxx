/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_INVOCATOR_HXX_
#define _SK_C_INVOCATOR_HXX_

#include <sk/C/handle.h>

namespace sk {
  namespace C {
    template<typename T, typename R>
    class invocator 
      : public virtual sk_c_handle::runnable
    {
      public:
        invocator(const sk::util::Mapper<T, R>& mapper, T& object, R& result);
        invocator(const invocator<T, R>& other);
        ~invocator();
    
        // sk_c_handle::Runnable implementation.
        void run() const;
    
      private:
        invocator<T, R>& operator = (const invocator<T, R>& other);

        const sk::util::Mapper<T, R>& _mapper;
        T& _object;
        R& _result;
    };
  }
}

#endif /* _SK_C_INVOCATOR_HXX_ */
