/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_NULLDEVICE_H_
#define _SK_IO_NULLDEVICE_H_

#include <sk/io/File.h>

namespace sk {
  namespace io {
    class NullDevice 
      : public sk::io::File
    {
      public:
        NullDevice();
        virtual ~NullDevice();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        NullDevice(const NullDevice& other);
        NullDevice& operator = (const NullDevice& other);
    };
  }
}

#endif /* _SK_IO_NULLDEVICE_H_ */
