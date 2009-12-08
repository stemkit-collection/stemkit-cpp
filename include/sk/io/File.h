/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

namespace sk {
  namespace io {
    class InputStream;
    class OutputStream;
    class FileInfo;

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

        const sk::io::FileInfo& info() const;

        sk::io::InputStream& inputStream() const;
        sk::io::OutputStream& outputStream() const;

        const sk::util::String getName() const;
        virtual sk::io::FileDescriptor& getFileDescriptor() const;
        virtual void close();
        uint64_t size() const;
        uint64_t position() const;
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        static bool exists(const sk::util::String& path);
        static bool isRegular(const sk::util::String& path);
        static bool isDirectory(const sk::util::String& path);
        static bool isPipe(const sk::util::String& path);
        static bool isDevice(const sk::util::String& path);
        static void unlink(const sk::util::String& path);
        static void rename(const sk::util::String& oldpath, const sk::util::String& newpath);
        
      private:
        File& operator = (const File& other);

        void open(const sk::util::String& mode, int permissions);
        void open(int mode, int permissions);
        int numericMode(const sk::util::String& mode);

        sk::util::String _name;
        sk::util::Holder<sk::io::FileDescriptor> _descriptorHolder;
        sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
        sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
        sk::util::Holder<sk::io::FileInfo> _infoHolder;
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
