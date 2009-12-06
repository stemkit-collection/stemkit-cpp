/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_DIR_H_
#define _SK_IO_DIR_H_

#include <sk/util/Object.h>
#include <sk/util/Pathname.h>
#include <sk/util/Holder.hxx>
#include <sk/util/Processor.h>

namespace sk {
  namespace io {
    class FileInfo;

    class Dir 
      : public virtual sk::util::Object
    {
      public:
        Dir(const sk::util::Pathname& path);
        virtual ~Dir();

        const sk::util::Pathname& getPath() const;
        void forEachEntry(const sk::util::Processor<const sk::io::FileInfo>& processor) const;
        void close();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Dir(const Dir& other);
        Dir& operator = (const Dir& other);
        
        const sk::util::Pathname _path;
        struct Data;
        sk::util::Holder<Data> _dataHolder;
    };
  }
}

#endif /* _SK_IO_DIR_H_ */
