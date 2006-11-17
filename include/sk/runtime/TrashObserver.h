/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RUNTIME_TRASHOBSERVER_
#define _SK_RUNTIME_TRASHOBSERVER_

#include <sk/util/Object.h>

namespace sk {
  namespace runtime {
    class TrashObserver
      : public virtual sk::util::Object 
    {
      public:
        TrashObserver();
        virtual ~TrashObserver();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
      
      private:
        TrashObserver(const TrashObserver& other);
        TrashObserver& operator = (const TrashObserver& other);
    };
  }
}

#endif /* _SK_RUNTIME_TRASHOBSERVER_ */
