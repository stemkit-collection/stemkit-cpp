/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEOUTPUTSTREAM_
#define _SK_IO_FILEOUTPUTSTREAM_

#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/io/FileStreamCoupler.hxx>
#include <sk/io/File.h>

namespace sk {
  namespace io {
    class FileOutputStream
      : public FileStreamCoupler<FileDescriptorOutputStream>
    {
      public:
        FileOutputStream(const sk::io::File& file);
        FileOutputStream(const sk::util::String& name);
        FileOutputStream(const sk::util::String& name, bool append);
        virtual ~FileOutputStream();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        FileOutputStream(const FileOutputStream& other);
        FileOutputStream& operator = (const FileOutputStream& other);
    };
  }
}

#endif /* _SK_IO_FILEOUTPUTSTREAM_ */
