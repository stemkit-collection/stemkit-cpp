/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILEINPUTSTREAM_
#define _SK_IO_FILEINPUTSTREAM_

#include <sk/io/FileDescriptorInputStream.h>
#include <sk/util/String.h>
#include <sk/io/File.h>

namespace sk {
  namespace io {
    class FileInputStream
      : public sk::io::FileDescriptorInputStream
    {
      public:
        FileInputStream(const sk::io::File& file);
        FileInputStream(const sk::util::String& name);
        virtual ~FileInputStream();

        const sk::io::File& getFile() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        FileInputStream(const FileInputStream& other);
        FileInputStream& operator = (const FileInputStream& other);

        sk::io::File _file;
    };
  }
}

#endif /* _SK_IO_FILEINPUTSTREAM_ */
