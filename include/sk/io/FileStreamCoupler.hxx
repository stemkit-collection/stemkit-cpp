/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILESTREAMCOUPLER_HXX_
#define _SK_IO_FILESTREAMCOUPLER_HXX_

#include <sk/io/File.h>
#include <sk/util/Holder.hxx>
#include <memory>

namespace sk {
  namespace io {
    template<typename S>
    class FileStreamCoupler
      : public S
    {
      public:
        FileStreamCoupler(std::auto_ptr<sk::io::File> file_auto_ptr);

        sk::io::File& getFile() const;
        
      private:
        FileStreamCoupler(const FileStreamCoupler& other);
        FileStreamCoupler& operator = (const FileStreamCoupler& other);

        sk::util::Holder<sk::io::File> _fileHolder;
    };
  }
}

#endif /* _SK_IO_FILESTREAMCOUPLER_HXX_ */
