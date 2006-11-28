/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_PTYSPECIFICS_
#define _SK_IO_PTYSPECIFICS_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileDescriptor;

    class PtySpecifics
      : public virtual sk::util::Object 
    {
      public:
        void setup();
        
        virtual int makeSlave(const sk::util::String& name) = 0;
        virtual int makeMaster(const sk::io::FileDescriptor& descriptor) = 0;
    };
  }
}

#endif /* _SK_IO_PTYSPECIFICS_ */
