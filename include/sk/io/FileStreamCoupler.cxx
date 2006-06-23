/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILESTREAMCOUPLER_
#define _SK_IO_FILESTREAMCOUPLER_

#include <sk/io/FileStreamCoupler.hxx>
#include <sk/util/Holder.cxx>

template<class Stream>
sk::io::FileStreamCoupler<Stream>::
FileStreamCoupler(std::auto_ptr<sk::io::File> file_auto_ptr)
  : Stream(file_auto_ptr.get()->getFileDescriptor().getFileNumber()), _fileHolder(file_auto_ptr.release())
{
}

template<class Stream>
sk::io::File&
sk::io::FileStreamCoupler<Stream>::
getFile() const
{
  return _fileHolder.get();
}

#endif /* _SK_IO_FILESTREAMCOUPLER_ */
