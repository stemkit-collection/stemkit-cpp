/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_STREAMPROVIDER_H_
#define _SK_IO_STREAMPROVIDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class InputStream;
    class OutputStream;

    class StreamProvider 
      : public virtual sk::util::Object
    {
      public:
        virtual sk::io::InputStream& inputStream() const = 0;
        virtual sk::io::OutputStream& outputStream() const = 0;
        virtual void close() = 0;
    };
  }
}

#endif /* _SK_IO_STREAMPROVIDER_H_ */
