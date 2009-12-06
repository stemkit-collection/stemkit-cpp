/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_FILEINFO_H_
#define _SK_IO_FILEINFO_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace io {
    class FileInfo 
      : public virtual sk::util::Object
    {
      public:
        FileInfo(const sk::util::String& path);
        FileInfo(int descriptor);
        FileInfo(const FileInfo& other);
        virtual ~FileInfo();

        const sk::util::String& getPath() const;
        uint64_t getSize() const;
        uint64_t getTimeAccessed() const;
        uint64_t getTimeModified() const;
        uint64_t getTimeUpdated() const;
        bool isDirectory() const;
        bool isRegular() const;
        bool isSymlink() const;
        bool isSocket() const;
        bool isPipe() const;
        bool isDevice() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        FileInfo& operator = (const FileInfo& other);

        struct Data;
        sk::util::Holder<Data> _dataHolder;
        const sk::util::String _path;
    };
  }
}

#endif /* _SK_IO_FILEINFO_H_ */
