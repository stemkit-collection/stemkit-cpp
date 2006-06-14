/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_EOFEXCEPTION_
#define _SK_IO_EOFEXCEPTION_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class EOFException
      : public virtual sk::util::Object 
    {
      public:
        EOFException();
        virtual ~EOFException();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        EOFException(const EOFException& other);
        EOFException& operator = (const EOFException& other);
    };
  }
}

#endif /* _SK_IO_EOFEXCEPTION_ */
