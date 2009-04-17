/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_STREAM_H_
#define _SK_IO_STREAM_H_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class Stream 
      : public virtual sk::util::Object
    {
      public:
        /// Closes this stream and releases any system resources
        /// associated with the stream.
        virtual void close() = 0;
        
        /// Instantiates another object of the same class as a copy 
        /// of itself.
        virtual Stream* clone() const = 0;
    };
  }
}

#endif /* _SK_IO_STREAM_H_ */
