/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_FILEDESCRIPTORPROVIDER_H_
#define _SK_IO_FILEDESCRIPTORPROVIDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace io {
    class FileDescriptor;

    class FileDescriptorProvider
      : public virtual sk::util::Object
    {
      public:
        virtual const sk::io::FileDescriptor& getFileDescriptor() const = 0;
    };
  }
}

#endif /* _SK_IO_FILEDESCRIPTORPROVIDER_H_ */
