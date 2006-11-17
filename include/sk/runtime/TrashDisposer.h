/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TRASHDISPOSER_
#define _SK_SYS_TRASHDISPOSER_

#include <sk/util/Object.h>

namespace sk {
  namespace sys {
    class TrashDisposer
      : public virtual sk::util::Object 
    {
      public:
        TrashDisposer();
        virtual ~TrashDisposer();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
      
      private:
        TrashDisposer(const TrashDisposer& other);
        TrashDisposer& operator = (const TrashDisposer& other);
    };
  }
}

#endif /* _SK_SYS_TRASHDISPOSER_ */
