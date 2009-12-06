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
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/Time.h>

namespace sk {
  namespace io {
    class FileInfo 
      : public virtual sk::util::Object
    {
      public:
        FileInfo(const sk::util::Pathname& path);
        FileInfo(int descriptor);
        FileInfo(const FileInfo& other);
        virtual ~FileInfo();

        const sk::util::String getType() const;
        const sk::util::Pathname& getPath() const;
        uint64_t getSize() const;
        const sk::rt::Time getTimeAccessed() const;
        const sk::rt::Time getTimeModified() const;
        const sk::rt::Time getTimeUpdated() const;
        bool isDirectory() const;
        bool isRegular() const;
        bool isSymlink() const;
        bool isSocket() const;
        bool isPipe() const;
        bool isDevice() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
    
      private:
        FileInfo& operator = (const FileInfo& other);

        struct Data;
        sk::util::Holder<Data> _dataHolder;
        const sk::util::Pathname _path;
    };
  }
}

#endif /* _SK_IO_FILEINFO_H_ */
