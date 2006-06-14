/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_DATAOUTPUTSTREAM_
#define _SK_IO_DATAOUTPUTSTREAM_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class DataOutputStream
      : public virtual sk::util::Object 
    {
      public:
        DataOutputStream();
        virtual ~DataOutputStream();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        DataOutputStream(const DataOutputStream& other);
        DataOutputStream& operator = (const DataOutputStream& other);
    };
  }
}

#endif /* _SK_IO_DATAOUTPUTSTREAM_ */
