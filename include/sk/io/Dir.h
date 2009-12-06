/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_DIR_H_
#define _SK_IO_DIR_H_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Dir 
      : public virtual sk::util::Object
    {
      public:
        Dir();
        virtual ~Dir();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Dir(const Dir& other);
        Dir& operator = (const Dir& other);
    };
  }
}

#endif /* _SK_IO_DIR_H_ */
