/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_IO_SELECTOR_REGULARFILE_H_
#define _SK_IO_SELECTOR_REGULARFILE_H_

#include <sk/util/Selector.h>
#include <sk/io/FileInfo.h>

namespace sk {
  namespace io {
    namespace selector {
      class RegularFile 
        : public virtual sk::util::Selector<const sk::io::FileInfo>
      {
        bool assess(const sk::io::FileInfo& info) const {
          return info.isRegular();
        }
      };
    }
  }
}

#endif /* _SK_IO_SELECTOR_REGULARFILE_H_ */
