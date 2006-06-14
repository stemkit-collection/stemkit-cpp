/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAOUTPUT_
#define _SK_IO_DATAOUTPUT_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class DataOutput
      : public virtual sk::util::Object 
    {
      public:
        DataOutput();
        virtual ~DataOutput();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        DataOutput(const DataOutput& other);
        DataOutput& operator = (const DataOutput& other);
    };
  }
}

#endif /* _SK_IO_DATAOUTPUT_ */
