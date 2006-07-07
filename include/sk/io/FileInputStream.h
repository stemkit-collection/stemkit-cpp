/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEINPUTSTREAM_
#define _SK_IO_FILEINPUTSTREAM_

#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileStreamCoupler.hxx>
#include <sk/util/String.h>
#include <sk/io/File.h>

namespace sk {
  namespace io {
    class FileInputStream
      : public FileStreamCoupler<FileDescriptorInputStream>
    {
      public:
        FileInputStream(const sk::io::File& file);
        FileInputStream(const sk::util::String& name);
        virtual ~FileInputStream();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        // sk::io::AbstractInputStream re-implementation.
        long long available() const;
        
      private:
        FileInputStream(const FileInputStream& other);
        FileInputStream& operator = (const FileInputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEINPUTSTREAM_ */
