/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_NULLDEVICEOUTPUTSTREAM_H_
#define _SK_IO_NULLDEVICEOUTPUTSTREAM_H_

#include <sk/io/FileOutputStream.h>

namespace sk {
  namespace io {
    class NullDeviceOutputStream 
      : public sk::io::FileOutputStream
    {
      public:
        NullDeviceOutputStream();
        virtual ~NullDeviceOutputStream();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        NullDeviceOutputStream(const NullDeviceOutputStream& other);
        NullDeviceOutputStream& operator = (const NullDeviceOutputStream& other);
    };
  }
}

#endif /* _SK_IO_NULLDEVICEOUTPUTSTREAM_H_ */
