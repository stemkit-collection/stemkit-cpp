/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_MAPPER_PATHNAMETOFILEINFO_H_
#define _SK_IO_MAPPER_PATHNAMETOFILEINFO_H_

#include <sk/util/Mapper.h>
#include <sk/util/Pathname.h>
#include <sk/io/FileInfo.h>

namespace sk {
  namespace io {
    namespace mapper {
      class PathnameToFileInfo 
        : public virtual sk::util::Mapper<const sk::util::Pathname, const sk::io::FileInfo> 
      {
        const sk::io::FileInfo map(const sk::util::Pathname& path) const {
          return sk::io::FileInfo(path);
        }
      };
    }
  }
}

#endif /* _SK_IO_MAPPER_PATHNAMETOFILEINFO_H_ */
