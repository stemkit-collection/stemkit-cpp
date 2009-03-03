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
    /**
     *  A class to perform %scope locking. This class will call method 
     *  lock() on a specified resource in the constructor and unlock() 
     *  in the destructor of the last instance in a copy chain. 
     *  Creating instances of this class on the stack (e.g. automatic
     *  variables or temporaries) will guarantee unlocking even in 
     *  presense of exceptions due to C++ stack unwinding feature.
     *
     *  Usage:
     *
     *  - Locking data member @c @b _mutex for the duration of an expression:
     *    @code
     *    ...
     *    ( sk::rt::Locker<sk::rt::Mutex>(_mutex), _a.calc() + _b.calc() );
     *    ...
     *    @endcode
     *    
     *  - Locking data member @c @b _mutex for the duration of a method:
     *    @code
     *    void someMethod() {
     *      sk::rt::Locker<sk::rt::Mutex> locker(_mutex);
     *    
     *      if(process() != 0) {
     *        throw sk::util::IllegalStateException("processing failed");
     *      }
     *    }
     *    @endcode
    */
    template<typename L>
    class Locker 
    {
      public:
        /**
         *  Constructs a locker class. The constructor will lock a 
         *  specified resource by calling its lock() method.
        */
        Locker(L& lock);
        /**
         *  Handles the locker instance destruction. When this locker 
         *  goes out of %scope, it will call unlock() on the resource 
         *  it has been costructed with, when it is the last instance 
         *  in a copy chain.
        */
        ~Locker();
    
      private:
        sk::util::Holder<L, sk::util::slot::policy::Sharing<L> > _lockHolder;
    };
  }
}

#endif /* _SK_RT_LOCKER_HXX_ */
