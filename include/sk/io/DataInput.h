/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAINPUT_
#define _SK_IO_DATAINPUT_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class DataInput
      : public virtual sk::util::Object 
    {
      public:
        DataInput();
        virtual ~DataInput();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        DataInput(const DataInput& other);
        DataInput& operator = (const DataInput& other);
    };
  }
}

#endif /* _SK_IO_DATAINPUT_ */
