/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILE_
#define _SK_IO_FILE_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/util/String.h>
#include <sk/io/FileDescriptor.h>

struct stat;

namespace sk {
  namespace io {
    class File
      : public virtual sk::util::Object 
    {
      public:
        File(const sk::util::String& name);
        File(const sk::util::String& name, const sk::util::String& mode);
        File(const sk::util::String& name, const sk::util::String& mode, int permissions);
        File(const sk::util::String& name, int mode);
        File(const sk::util::String& name, int mode, int permissions);
        File(const File& other);
        virtual ~File();

        const sk::util::String getName() const;
        sk::io::FileDescriptor& getFileDescriptor() const;
        void close();
        long long size() const;
        long long position() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        
      private:
        File& operator = (const File& other);

        void open(const sk::util::String& mode, int permissions);
        void open(int mode, int permissions);
        int numericMode(const sk::util::String& mode);
        struct ::stat& stat() const;

        sk::util::String _name;
        sk::util::Holder<sk::io::FileDescriptor> _descriptorHolder;
        mutable sk::util::Holder<struct ::stat> _statHolder;
    };
  }
}

#if 0
  Mode |  Meaning
  -----+--------------------------------------------------------
  "r"  |  Read-only, starts at beginning of file  (default mode).
  -----+--------------------------------------------------------
  "r+" |  Read-write, starts at beginning of file.
  -----+--------------------------------------------------------
  "w"  |  Write-only, truncates existing file
       |  to zero length or creates a new file for writing.
  -----+--------------------------------------------------------
  "w+" |  Read-write, truncates existing file to zero length
       |  or creates a new file for reading and writing.
  -----+--------------------------------------------------------
  "a"  |  Write-only, starts at end of file if file exists,
       |  otherwise creates a new file for writing.
  -----+--------------------------------------------------------
  "a+" |  Read-write, starts at end of file if file exists,
       |  otherwise creates a new file for reading and
       |  writing.
  -----+--------------------------------------------------------
   "b" |  (DOS/Windows only) Binary file mode (may appear with
       |  any of the key letters listed above).
#endif
  
#endif /* _SK_IO_FILE_ */
