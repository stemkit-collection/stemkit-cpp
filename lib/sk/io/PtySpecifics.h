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
    class PtySpecifics
      : public virtual sk::util::Object 
    {
      public:
        PtySpecifics();
        virtual ~PtySpecifics();

        void setup();
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        PtySpecifics(const PtySpecifics& other);
        PtySpecifics& operator = (const PtySpecifics& other);
    };
  }
}

#endif /* _SK_IO_PTYSPECIFICS_ */
