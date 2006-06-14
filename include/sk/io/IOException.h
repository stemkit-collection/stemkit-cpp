/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_IOEXCEPTION_
#define _SK_IO_IOEXCEPTION_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class IOException
      : public virtual sk::util::Object 
    {
      public:
        IOException();
        virtual ~IOException();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        IOException(const IOException& other);
        IOException& operator = (const IOException& other);
    };
  }
}

#endif /* _SK_IO_IOEXCEPTION_ */
